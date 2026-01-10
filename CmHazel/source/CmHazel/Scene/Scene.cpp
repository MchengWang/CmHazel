#include "cmzpch.h"
#include "Scene.h"

#include "Components.h"
#include "ScriptableEntity.h"
#include "CmHazel/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

// Box2D
#include "box2d/box2d.h"
#include "box2d/base.h"
#include "box2d/collision.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"

namespace CmHazel
{

	void SyncFixedRotation(b2BodyId bodyId, float lockedAngle)
	{
		b2Vec2 pos = b2Body_GetPosition(bodyId);
		b2Body_SetTransform(bodyId, pos, b2MakeRot(lockedAngle));
		b2Body_SetAngularVelocity(bodyId, 0.0f);
	}

	static b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
	{
		switch (bodyType)
		{
		case CmHazel::Rigidbody2DComponent::BodyType::Static:			return b2_staticBody;
		case CmHazel::Rigidbody2DComponent::BodyType::Dynamic:			return b2_dynamicBody;
		case CmHazel::Rigidbody2DComponent::BodyType::Kinematic:		return b2_kinematicBody;
		}

		CM_CORE_ASSERT(false, "Unkown body type");
		return b2_staticBody;
	}

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
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
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnRuntimeStart()
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
			bodyDef.type = Rigidbody2DTypeToBox2DBody(rb2d.Type);
			bodyDef.position = { transform.Translation.x, transform.Translation.y };
			bodyDef.rotation = b2MakeRot(transform.Rotation.z);
			
			b2BodyId bodyId = b2CreateBody(m_PhysicsWorld, &bodyDef);

			rb2d.RuntimeBody = bodyId;

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

				b2ShapeId ss =  b2CreatePolygonShape(
					bodyId, // BodyId
					&shapeDef,
					&box
				);

			}
			
		}
	}

	void Scene::OnRuntimeStop()
	{
		b2DestroyWorld(m_PhysicsWorld);
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
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
			const float timeStep = ts;
			const int32_t subStepCount = 1; // 3.x 用 substeps，不再分 velocity / position
			b2World_Step(m_PhysicsWorld, timeStep, subStepCount);

			// 从 Box2D 获取变换
			auto view = m_Registry.view<Rigidbody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { e, this };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

				b2BodyId body = rb2d.RuntimeBody;
				b2Vec2 position = b2Body_GetPosition(body);
				b2Transform xf = b2Body_GetTransform(body);
				float angle = b2Rot_GetAngle(xf.q);

				transform.Translation.x = position.x;
				transform.Translation.y = position.y;
				transform.Rotation.z = angle;
			}
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;

		{

			m_Registry.view<TransformComponent, CameraComponent>()
				.each([&](TransformComponent& transform, CameraComponent& camera)
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

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{	
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

	template <typename T>
	void Scene::OnComponentAdded(Entity, T&)
	{
		//static_assert(false);
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
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity, SpriteRendererComponent&)
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

}