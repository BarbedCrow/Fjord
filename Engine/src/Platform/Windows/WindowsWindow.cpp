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
		FJORD_CORE_ASSERT(!isGLFWInitialized, "GLFW was already initialized");

		int success = glfwInit();
		FJORD_CORE_ASSERT(success, "Couldn't initialize GLFW");
		isGLFWInitialized = true;

		//glfwWindowHint(GLFW_SAMPLES, 4); // MULTISAMPLING
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_Window, this);
		SetVSync(true);

		OnWindowClose = CreateRef<Event<>>(this);
		OnWindowResize = CreateRef<Event<uint32_t, uint32_t>>(this);

		SetCallbacks();
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetCallbacks()
	{
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* m_Window)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				window->OnWindowClose->Invoke(window);
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* m_Window, int width, int height)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				window->OnWindowResize->Invoke(window, width, height);
			});
	}

}