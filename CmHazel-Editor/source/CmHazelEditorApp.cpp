#include <CmHazel.h>
#include <CmHazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace CmHazel
{

	class CmHazelEditor : public Application
	{
	public:
		CmHazelEditor()
			: Application("CmHazel Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~CmHazelEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new CmHazelEditor();
	}

}