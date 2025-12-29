#include <CmHazel.h>

class ExampleLayer : public CmHazel::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		CM_INFO("ExampleLayer::Update");
	}

	void OnEvent(CmHazel::Event& event) override
	{
		CM_TRACE("{0}", event.ToString());
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