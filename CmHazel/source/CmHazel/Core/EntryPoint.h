#pragma once
#include "CmHazel/Core/Base.h"
#include "CmHazel/Core/Application.h"

#ifdef CM_PLATFORM_WINDOWS

extern CmHazel::Application* CmHazel::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv)
{
	// 初始化引擎日志
	CmHazel::Log::Init();

	CM_PROFILE_BEGIN_SESSION("Startup", "CmHazelProfile-Startup.json");
	auto app = CmHazel::CreateApplication({ argc, argv });
	CM_PROFILE_END_SESSION();

	CM_PROFILE_BEGIN_SESSION("Runtime", "CmHazelProfile-Runtime.json");
	app->Run();
	CM_PROFILE_END_SESSION();

	CM_PROFILE_BEGIN_SESSION("Shutdown", "CmHazelProfile-Shutdown.json");
	delete app;
	CM_PROFILE_END_SESSION();
}

#else
#error CmHazel only supports Windows!
#endif // CM_PLATFORM_WINDOWS
