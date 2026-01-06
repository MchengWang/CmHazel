#include <CmHazel.h>
#include <CmHazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace CmHazel
{

	class CmEditor : public Application
	{
	public:
		CmEditor()
			: Application("CmEditor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~CmEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new CmEditor();
	}

}