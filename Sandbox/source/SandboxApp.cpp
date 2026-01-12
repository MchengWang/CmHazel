#include <CmHazel.h>
#include <CmHazel/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

#include "ExampleLayer.h"

class Sandbox : public CmHazel::Application
{
public:
	Sandbox(const CmHazel::ApplicationSpecification& specification)
		: CmHazel::Application(specification)
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

CmHazel::Application* CmHazel::CreateApplication(CmHazel::ApplicationCommandLineArgs args)
{

	CmHazel::ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Hazelnut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}