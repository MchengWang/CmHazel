#include <CmHazel.h>

class Sandbox : public CmHazel::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

CmHazel::Application* CmHazel::CreateApplication()
{
	return new Sandbox();
}