#pragma once

#include <GLFW/glfw3.h>

#include "Fjord/core/Window.h"

namespace Fjord
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(std::string name, uint32_t width, uint32_t height);
		~WindowsWindow();

		virtual void Update() override;

		virtual void* GetNativeWindow() const override { return m_Window; }

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetVSync(bool isVsync) override { m_VSync = isVsync; glfwSwapInterval(m_VSync); }
		virtual bool IsVSync() const override { return m_VSync; }

	private:
		std::string m_Name;
		uint32_t m_Width, m_Height;
		bool m_VSync;

		GLFWwindow* m_Window;
	};
}

