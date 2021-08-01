#include "fjordpch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

#include "Fjord/core/Application.h"

namespace Fjord
{
	bool Input::IsKeyPressed(int code)
	{
		Application& app = Application::Get();
		auto window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());
		int state = glfwGetKey(window, code);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int code)
	{
		Application& app = Application::Get();
		auto window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());
		int state = glfwGetMouseButton(window, code);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		Application& app = Application::Get();
		auto window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { xPos, yPos };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePos();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePos();
		return y;
	}
}