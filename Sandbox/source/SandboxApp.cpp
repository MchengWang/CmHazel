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
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

CmHazel::Application* CmHazel::CreateApplication()
{
	return new Sandbox();
}