#include "cmzpch.h"
#include "ScriptGlue.h"

#include "mono/metadata/object.h"

namespace CmHazel
{

#define CM_ADD_INTERNAL_CALL(Name) mono_add_internal_call("CmHazel.InternalCalls::" #Name, Name);

	static void NativeLog(MonoString* string, int parameter)
	{
		char* cStr = mono_string_to_utf8(string);
		std::string str(cStr);
		mono_free(cStr);
		std::cout << str << ", " << parameter << std::endl;
	}

	static void NativeLog_Vector(glm::vec3* parameter, glm::vec3* outResult)
	{
		CM_CORE_WARN("Value: {0}, {1}, {2}", parameter->x, parameter->y, parameter->z);
		*outResult = glm::normalize(*parameter);
	}

	static float NativeLog_VectorDot(glm::vec3* parameter)
	{
		CM_CORE_WARN("Value: {0}, {1}, {2}", parameter->x, parameter->y, parameter->z);
		return glm::dot(*parameter, *parameter);
	}

	void ScriptGlue::RegisterFunctions()
	{
		CM_ADD_INTERNAL_CALL(NativeLog);
		CM_ADD_INTERNAL_CALL(NativeLog_Vector);
		CM_ADD_INTERNAL_CALL(NativeLog_VectorDot);
	}

}