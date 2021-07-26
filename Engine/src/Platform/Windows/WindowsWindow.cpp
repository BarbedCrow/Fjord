#include "fjordpch.h"
#include "WindowsWindow.h"

namespace Fjord
{
	static bool isGLFWInitialized = false;

	Scope<Window> Window::Create(std::string name, uint32_t width, uint32_t height)
	{
		return CreateScope<WindowsWindow>(name, width, height);
	}
	
	WindowsWindow::WindowsWindow(std::string name, uint32_t width, uint32_t height) : m_Name(name), m_Width(width), m_Height(height)
	{
		if (!isGLFWInitialized)
		{
			int success = glfwInit();
			FJORD_CORE_ASSERT(success, "Couldn't initialize GLFW");
			isGLFWInitialized = true;

			//glfwWindowHint(GLFW_SAMPLES, 4); // MULTISAMPLING
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);

			glfwSetWindowUserPointer(m_Window, this);
			SetVSync(true);
		}
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

}