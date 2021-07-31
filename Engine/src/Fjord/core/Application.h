#pragma once

#include "Core.h"
#include "Window.h"

#include "entt/entt.hpp"

//REMOVE
#include "Fjord/Render/Buffer.h"
#include "Fjord/Render/Shader.h"
#include "Fjord/Render/VertexArray.h"

namespace Fjord
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Update();

		Window* GetWindow() const { return m_Window.get(); }
		inline static Application& Get() { return *s_Instance; }
	private:
		virtual bool HandleOnWindowClose();
		virtual bool HandleOnWindowResize(uint32_t width, uint32_t height);
	private:
		Scope<Window> m_Window;

		bool m_Running = true;

		static Application* s_Instance;

		//REMOVE
		glm::vec4 testColor = glm::vec4(1.f);
		Ref<VertexArray> m_VertexArray;
	};

	Application* CreateApplication();
}

