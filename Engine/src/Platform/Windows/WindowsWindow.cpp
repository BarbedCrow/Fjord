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
		
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		SetVSync(true);

		OnWindowClose = CreateRef<Event<>>(this);
		OnWindowResize = CreateRef<Event<uint32_t, uint32_t>>(this);
		OnKeyPressed = CreateRef<Event<uint8_t, uint8_t>>(this);
		OnKeyReleased = CreateRef<Event<uint8_t>>(this);
		OnKeyTyped = CreateRef<Event<uint8_t>>(this);
		OnMouseButtonPressed = CreateRef<Event<uint8_t>>(this);
		OnMouseButtonReleased = CreateRef<Event<uint8_t>>(this);
		OnMouseScrolled = CreateRef<Event<float, float>>(this);
		OnMouseMoved = CreateRef<Event<uint32_t, uint32_t>>(this);

		SetCallbacks();
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
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
		glfwSetKeyCallback(m_Window, [](GLFWwindow* m_Window, int key, int scancode, int action, int mods)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				switch (action)
				{
				case GLFW_PRESS:
					window->OnKeyPressed->Invoke(window, key, 0);
					break;
				case GLFW_REPEAT:
					window->OnKeyPressed->Invoke(window, key, 1);
					break;
				case GLFW_RELEASE:
					window->OnKeyReleased->Invoke(window, key);
					break;
				default:
					break;
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* m_Window, unsigned int codepoint)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				window->OnKeyTyped->Invoke(window, codepoint);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* m_Window, int button, int action, int mods)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				switch (action)
				{
				case GLFW_PRESS:
					window->OnMouseButtonPressed->Invoke(window, button);
					break;
				case GLFW_RELEASE:
					window->OnMouseButtonReleased->Invoke(window, button);
					break;
				default:
					break;
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* m_Window, double xOffset, double yOffset)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				window->OnMouseScrolled->Invoke(window, (float)xOffset, (float)yOffset);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* m_Window, double xPos, double yPos)
			{
				WindowsWindow* window = (WindowsWindow*)glfwGetWindowUserPointer(m_Window);
				window->OnMouseMoved->Invoke(window, (float)xPos, (float)yPos);
			});
	}

}