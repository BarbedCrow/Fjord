#pragma once

#include <glm/glm.hpp>

namespace Fjord
{
	struct ComponentMember
	{
		std::string Name;
		bool IsEditable;

		ComponentMember() = default;
		virtual ~ComponentMember() {}
		ComponentMember(std::string name, bool isEditable = true)
			:
			Name(name), IsEditable(isEditable) {}
	};

	
	struct ComponentMemberVec3 : ComponentMember
	{
		glm::vec3* Value;

		float MinVal;
		float MaxVal;
		float ChangeSpeed;

		ComponentMemberVec3(std::string name, 
			glm::vec3* value, 
			float minVal = -1024.f, 
			float maxVal = 1024.f, 
			float changeSpeed = 0.1f,
			bool isEditable = true) 
			: 
			ComponentMember(name, isEditable), 
			Value(value),
			MinVal(minVal),
			MaxVal(maxVal),
			ChangeSpeed(changeSpeed)
		{}
	};


	struct ComponentMemberColorRGBA : ComponentMember
	{
		glm::vec4* Value;

		ComponentMemberColorRGBA(std::string name, glm::vec4* value, bool isEditable = true)
			:
			ComponentMember(name, isEditable),
			Value(value)
		{}
	};

	struct ComponentMemberString : ComponentMember
	{
		std::string* Value;

		ComponentMemberString(std::string name, std::string* value, bool isEditable = true)
			:
			ComponentMember(name, isEditable),
			Value(value)
		{}
	};

	struct ComponentProxy
	{
		std::string Name;
		std::vector<Ref<ComponentMember>> Members;
	};
}