#include <CmHazel.h>
#include <CmHazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace CmHazel
{

	class CmEditor : public Application
	{
	public:
		CmEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "CmEditor";
		spec.CommandLineArgs = args;

		return new CmEditor(spec);
	}

}