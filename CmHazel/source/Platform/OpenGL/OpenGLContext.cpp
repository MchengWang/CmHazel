#include "cmzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace CmHazel
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CM_CORE_ASSERT(windowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		CM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CM_CORE_ASSERT(status, "Failed to intialized Glad");

		CM_CORE_INFO("OpenGL Info: ");
		CM_CORE_INFO("	Vendor: {0}", (char*)glGetString(GL_VENDOR));
		CM_CORE_INFO("	Renderer: {0}", (char*)glGetString(GL_RENDERER));
		CM_CORE_INFO("	Version: {0}", (char*)glGetString(GL_VERSION));

		CM_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "CmHazel requires at least OpenGL version 4.5!");

	}

	void OpenGLContext::SwapBuffers()
	{
		CM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}