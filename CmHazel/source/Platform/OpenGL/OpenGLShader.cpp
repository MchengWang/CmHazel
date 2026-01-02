#include "cmzpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

namespace CmHazel
{

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// 创建一个空的顶点着色器句柄
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// 将顶点着色器源码给 GL
		// 注意，当 std::string's.c_str() 为空的时候结束
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// 编译顶点着色器
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength 包括 空字符
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// 我们不在需要这个着色器了
			glDeleteShader(vertexShader);

			CM_CORE_ERROR("{0}", infoLog.data());
			CM_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// 创建一个空的片段着色器句柄
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// 将片段着色器源码给 GL
		// 注意，当 std::string's.c_str() 为空的时候结束
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// 编译片段着色器
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength 包括 空字符
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// 我们不在需要这个着色器了
			glDeleteShader(fragmentShader);
			//他们任何一个都可以。不要泄露着色器
			glDeleteShader(vertexShader);

			CM_CORE_ERROR("{0}", infoLog.data());
			CM_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// 顶点和片段着色器都成功编译了
		// 现在将他们一起连接到一个进展中
		// 获取一个进程对象
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// 将我们的着色器附加到进程中
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// 连接我们的进程
		glLinkProgram(program);

		// 注意这里的不同函数：使用 glGetProgram* 而不是 glGetShader*。
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength 包括 空字符
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// 我们不在需要这个进程了
			glDeleteProgram(program);
			//他们任何一个都可以。不要泄露着色器
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			CM_CORE_ERROR("{0}", infoLog.data());
			CM_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// 链接成功后分离所有着色器
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}