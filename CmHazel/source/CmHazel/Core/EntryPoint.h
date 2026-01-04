#pragma once
#include "CmHazel/Core/Core.h"

#ifdef CM_PLATFORM_WINDOWS

extern CmHazel::Application* CmHazel::CreateApplication();

int main()
{
	// 初始化引擎日志
	CmHazel::Log::Init();

	CM_CORE_WARN("Initialized Log!");
	int a = 10;
	CM_INFO("Hello! Var = {0}", a);

	auto app = CmHazel::CreateApplication();
	app->Run();
	delete app;
}

#else
#error CmHazel only supports Windows!
#endif // CM_PLATFORM_WINDOWS
