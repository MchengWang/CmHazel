#pragma once

#ifdef CM_PLATFORM_WINDOWS

extern CmHazel::Application* CmHazel::CreateApplication();

int main()
{
	printf("CmHazel Engine!\n");
	auto app = CmHazel::CreateApplication();
	app->Run();
	delete app;
}

#else
#error CmHazel only supports Windows!
#endif // CM_PLATFORM_WINDOWS
