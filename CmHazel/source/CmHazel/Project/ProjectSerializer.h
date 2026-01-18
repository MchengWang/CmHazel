#pragma once

#include "Project.h"

namespace CmHazel
{

	class ProjectSerializer
	{
	public:
		ProjectSerializer(Shared<Project> project);

		bool Serialize(const std::filesystem::path& filepath);
		bool Deserialize(const std::filesystem::path& filepath);

	private:
		Shared<Project> m_Project;

	};

}