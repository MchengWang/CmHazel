#include "cmzpch.h"
#include "Scene.h"

#include "Components.h"
#include "ScriptableEntity.h"
#include "CmHazel/Scripting/ScriptEngine.h"
#include "CmHazel/Renderer/Renderer2D.h"
#include "CmHazel/Physics/Physics2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

// Box2D
#include "box2d/box2d.h"
#include "box2d/base.h"
#include "box2d/collision.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

/*
*  bug
* 在拖拽文件到视口时，容易造成上下文不一致
* 从而中断
*/

namespace CmHazel
{

	void SyncFixedRotation(b2BodyId bodyId, float lockedAngle)
	{
		b2Vec2 pos = b2Body_GetPosition(bodyId);
		b2Body_SetTransform(bodyId, pos, b2MakeRot(lockedAngle));
		b2Body_SetAngularVelocity(bodyId, 0.0f);
	}

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	template<typename... Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		([&]()
			{
				auto view = src.view<Component>();
				for (auto srcEntity : view)
				{
					entt::entity dstEntity = enttMap.at(src.get<IDComponent>(srcEntity).ID);

					auto& srcComponent = src.get<Component>(srcEntity);
					dst.emplace_or_replace<Component>(dstEntity, srcComponent);
				}
			}(), ...);
	}

	template<typename... Component>
	static void CopyComponent(ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		CopyComponent<Component...>(dst, src, enttMap);
	}

	template<typename... Component>
	static void CopyComponentIfExists(Entity dst, Entity src)
	{
		([&]()
			{
				if (src.HasComponent<Component>())
					dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
			}(), ...);
	}

	template<typename... Component>
	static void CopyComponentIfExists(ComponentGroup<Component...>, Entity dst, Entity src)
	{
		CopyComponentIfExists<Component...>(dst, src);
	}

	Shared<Scene> Scene::Copy(Shared<Scene> other)
	{
		Shared<Scene> newScene = CreateShared<Scene>();

		newScene->m_ViewportWidth = other->m_ViewportWidth;
		newScene->m_ViewportHeight = other->m_ViewportHeight;

		auto& srcSceneRegistry = other->m_Registry;
		auto& dstSceneRegistry = newScene->m_Registry;
		std::unordered_map<UUID, entt::entity> enttMap;

		// 在新的场景中创建实体
		auto idView = srcSceneRegistry.view<IDComponent>();
		for (auto e : idView)
		{
			UUID uuid = srcSceneRegistry.get<IDComponent>(e).ID;
			const auto& name = srcSceneRegistry.get<TagComponent>(e).Tag;
			Entity newEntity = newScene->CreateEntityWithUUID(uuid, name);
			enttMap[uuid] = (entt::entity)newEntity;
		}

		// 复制组件 (除了 IDComponent 和 TagComponent)
		CopyComponent(AllComponents{}, dstSceneRegistry, srcSceneRegistry, enttMap);

		return newScene;
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<IDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		m_EntityMap[uuid] = entity;

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_EntityMap.erase(entity.GetUUID());
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeStart()
	{
		m_IsRunning = true;

		OnPhysics2DStart();

		// Scripting
		{
			ScriptEngine::OnRuntimeStart(this);

			// Instantiate all script entities;

			auto view = m_Registry.view<ScriptComponent>();
			for (auto e : view)
			{
				Entity entity = { e, this };
				ScriptEngine::OnCreateEntity(entity);
			}
		}
	}

	void Scene::OnRuntimeStop()
	{
		m_IsRunning = false;

		OnPhysics2DStop();

		ScriptEngine::OnRuntimeStop();
	}

	void Scene::OnSimulationStart()
	{
		OnPhysics2DStart();
	}

	void Scene::OnSimulationStop()
	{
		OnPhysics2DStop();
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		if (!m_IsPaused || m_StepFrames-- > 0)
		{
			// Update scripts
			{
				// C# Entity OnUpdate
				auto view = m_Registry.view<ScriptComponent>();
				for (auto e : view)
				{
					Entity entity = { e, this };
					ScriptEngine::OnUpdateEntity(entity, ts);
				}

				m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
					{
						// TODO: Move to Scene::OnScenePlay
						if (!nsc.Instance)
						{
							nsc.Instance = nsc.InstantiateScript();
							nsc.Instance->m_Entity = Entity{ entity, this };
							nsc.Instance->OnCreate();
						}

						nsc.Instance->OnUpdate(ts);
					});
			}


			// Physics
			{
				constexpr int subStepCount = 4;
				b2World_Step(m_PhysicsWorld, ts, subStepCount);

				// Retrieve transform from Box2D
				auto view = m_Registry.view<Rigidbody2DComponent>();
				for (auto e : view)
				{
					Entity entity = { e, this };
					auto& transform = entity.GetComponent<TransformComponent>();
					auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

					b2BodyId body = rb2d.RuntimeBody;
					const auto& tf = b2Body_GetTransform(body);
					transform.Translation.x = tf.p.x;
					transform.Translation.y = tf.p.y;
					transform.Rotation.z = b2Rot_GetAngle(tf.q);
				}
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			m_Registry.view<TransformComponent, CameraComponent>()
				.each([&mainCamera, &cameraTransform](TransformComponent& transform, CameraComponent& camera) 
				{
					if (camera.Primary)
					{
						mainCamera = &camera.Camera;
						cameraTransform = transform.GetTransform();
					}
				});
		}

		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			// Draw sprites
			{
				auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
				for (auto entity : group)
				{
					auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

					Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
				}
			}

			// Draw circles
			{
				m_Registry.view<TransformComponent, CircleRendererComponent>()
					.each([](entt::entity entity, TransformComponent transform, CircleRendererComponent circle)
					{
						Renderer2D::DrawCircle(transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
					});
			}

			Renderer2D::EndScene();
		}

	}

	void Scene::OnUpdateSimulation(Timestep ts, EditorCamera& camera)
	{
		if (!m_IsPaused || m_StepFrames-- > 0)
		{
			// Physics
			{
				constexpr int subStepCount = 4;
				b2World_Step(m_PhysicsWorld, ts, subStepCount);

				// Retrieve transform from Box2D
				auto view = m_Registry.view<Rigidbody2DComponent>();
				for (auto e : view)
				{
					Entity entity = { e, this };
					auto& transform = entity.GetComponent<TransformComponent>();
					auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

					b2BodyId body = rb2d.RuntimeBody;
					const auto& position = b2Body_GetTransform(body);
					transform.Translation.x = position.p.x;
					transform.Translation.y = position.p.y;
					transform.Rotation.z = b2Rot_GetAngle(position.q);
				}
			}
		}

		// Render
		RenderScene(camera);
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		// Render
		RenderScene(camera);
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{	
		if (m_ViewportWidth == width && m_ViewportHeight == height)
			return;

		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// 调整我们非固定纵横比相机的大小
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

	void Scene::Step(int frames)
	{
		m_StepFrames = frames;
	}

	Entity Scene::DuplicateEntity(Entity entity)
	{
		// 复制名称，因为我们将修改组件数据结构
		std::string name = entity.GetName();
		Entity newEntity = CreateEntity(name);
		CopyComponentIfExists(AllComponents{}, newEntity, entity);
		return newEntity;
	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}

		return {};
	}

	Entity Scene::FindEntityByName(std::string_view name)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			const TagComponent& tc = view.get<TagComponent>(entity);
			if (tc.Tag == name)
				return Entity{ entity, this };
		}

		return { };
	}

	Entity Scene::GetEntityByUUID(UUID uuid)
	{
		// 也许应该使用 assert
		if (m_EntityMap.find(uuid) != m_EntityMap.end())
			return { m_EntityMap.at(uuid), this };

		return {};
	}

	void Scene::OnPhysics2DStart()
	{
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = { 0.0f, -9.8f };
		m_PhysicsWorld = b2CreateWorld(&worldDef);

		auto view = m_Registry.view<Rigidbody2DComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this };
			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = Utils::Rigidbody2DTypeToBox2DBody(rb2d.Type);
			bodyDef.position = { transform.Translation.x, transform.Translation.y };
			bodyDef.rotation = b2MakeRot(transform.Rotation.z);

			b2BodyId bodyId = b2CreateBody(m_PhysicsWorld, &bodyDef);

			// 固定旋转则使用每一帧都回正来固定旋转
			if (rb2d.FixedRotation)
				SyncFixedRotation(bodyId, 0.0f);
			rb2d.RuntimeBody = bodyId;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();

				b2Polygon box = b2MakeBox(
					bc2d.Size.x * transform.Scale.x,
					bc2d.Size.y * transform.Scale.y
				);

				worldDef.restitutionThreshold = bc2d.RestitutionThreshold;

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = bc2d.Density;
				shapeDef.material.friction = bc2d.Friction;
				shapeDef.material.restitution = bc2d.Restitution;

				b2ShapeId ss = b2CreatePolygonShape(
					bodyId, // BodyId
					&shapeDef,
					&box
				);
			}

			if (entity.HasComponent<CircleCollider2DComponent>())
			{
				auto& cc2d = entity.GetComponent<CircleCollider2DComponent>();

				b2Circle circleShape;
				circleShape.center = { cc2d.Offset.x, cc2d.Offset.y };
				circleShape.radius = transform.Scale.x * cc2d.Radius;

				worldDef.restitutionThreshold = cc2d.RestitutionThreshold;

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				shapeDef.density = cc2d.Density;
				shapeDef.material.friction = cc2d.Friction;
				shapeDef.material.restitution = cc2d.Restitution;

				b2CreateCircleShape(bodyId, &shapeDef, &circleShape);
			}
		}
	}

	void Scene::OnPhysics2DStop()
	{
		b2DestroyWorld(m_PhysicsWorld);
		m_PhysicsWorld = b2_nullWorldId;
	}

	void Scene::RenderScene(EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);


		// Draw sprites
		{
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}
		}

		// Draw circles
		{
			m_Registry.view<TransformComponent, CircleRendererComponent>()
				.each([&](entt::entity entity, TransformComponent transform, CircleRendererComponent circle)
				{
					Renderer2D::DrawCircle(transform.GetTransform(), circle.Color, circle.Thickness, circle.Fade, (int)entity);
				});
		}

		Renderer2D::DrawString("CM", Font::GetDefault(), glm::mat4(1.0f), glm::vec4(1.0f));
		Renderer2D::DrawString(
			R"(
			// MSDF text shader

			#type vertex
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			layout(location = 2) in vec2 a_TexCoord;
			layout(location = 3) in int a_EntityID;

			layout(std140, binding = 0) uniform Camera
			{
				mat4 u_ViewProjection;
			};

			struct VertexOutput
			{
				vec4 Color;
				vec2 TexCoord;
			};

			layout (location = 0) out VertexOutput Output;
			layout (location = 2) out flat int v_EntityID;

			void main()
			{
				Output.Color = a_Color;
				Output.TexCoord = a_TexCoord;
				v_EntityID = a_EntityID;

				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

			#type fragment
			#version 450 core

			layout(location = 0) out vec4 o_Color;
			layout(location = 1) out int o_EntityID;

			struct VertexOutput
			{
				vec4 Color;
				vec2 TexCoord;
			};

			layout (location = 0) in VertexOutput Input;
			layout (location = 2) in flat int v_EntityID;

			layout (binding = 0) uniform sampler2D u_FontAtlas;

			float screenPxRange() {
				const float pxRange = 2.0; // set to distance field's pixel range
				vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
				vec2 screenTexSize = vec2(1.0)/fwidth(Input.TexCoord);
				return max(0.5*dot(unitRange, screenTexSize), 1.0);
			}

			float median(float r, float g, float b) {
				return max(min(r, g), min(max(r, g), b));
			}

			void main()
			{
				vec4 texColor = Input.Color * texture(u_FontAtlas, Input.TexCoord);

				vec3 msd = texture(u_FontAtlas, Input.TexCoord).rgb;
				float sd = median(msd.r, msd.g, msd.b);
				float screenPxDistance = screenPxRange()*(sd - 0.5);
				float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
				if (opacity == 0.0)
					discard;

				vec4 bgColor = vec4(0.0);
				o_Color = mix(bgColor, Input.Color, opacity);
				if (o_Color.a == 0.0)
					discard;
	
				o_EntityID = v_EntityID;
			}
			)"
			, Font::GetDefault(), glm::mat4(1.0f), glm::vec4(1.0f));

		Renderer2D::EndScene();
	}

	template <typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(sizeof(T) == 0);
	}

	template <>
	void Scene::OnComponentAdded<IDComponent>(Entity entity, IDComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template <>
	void Scene::OnComponentAdded<ScriptComponent>(Entity, ScriptComponent&)
	{

	}

	template <>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity, SpriteRendererComponent&)
	{
	}

	template<>
	void Scene::OnComponentAdded<CircleRendererComponent>(Entity entity, CircleRendererComponent& component)
	{
	}

	template <>
	void Scene::OnComponentAdded<TagComponent>(Entity, TagComponent&)
	{
	}

	template <>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity, NativeScriptComponent&)
	{
	}

	template <>
	void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity, Rigidbody2DComponent&)
	{
	}

	template <>
	void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity, BoxCollider2DComponent&)
	{
	}

	template <>
	void Scene::OnComponentAdded<CircleCollider2DComponent>(Entity, CircleCollider2DComponent&)
	{
	}

}