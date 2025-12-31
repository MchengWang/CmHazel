#include <CmHazel.h>

#include "imgui/imgui.h"

class ExampleLayer : public CmHazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (CmHazel::Input::IsKeyPressed(CM_KEY_TAB))
			CM_TRACE("Tab key is pressed (poll)£¡");
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(CmHazel::Event& event) override
	{
		if (event.GetEventType() == CmHazel::EventType::KeyPressed)
		{
			CmHazel::KeyPressedEvent& e = (CmHazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == CM_KEY_TAB)
				CM_TRACE("Tab key is pressed (event)!");
			CM_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public CmHazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

CmHazel::Application* CmHazel::CreateApplication()
{
	return new Sandbox();
}