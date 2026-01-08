#include <CmHazel.h>
#include <CmHazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace CmHazel
{

	class CmEditor : public Application
	{
	public:
		CmEditor(ApplicationCommandLineArgs args)
			: Application("CmEditor", args)
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~CmEditor()
		{

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new CmEditor(args);
	}

}