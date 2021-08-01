#pragma once

#include <string>

#include "Core.h"
#include "Fjord/core/Event.h"

namespace Fjord
{
	class Window
	{
	public:
		Ref<Event<>> OnWindowClose;
		Ref<Event<uint32_t, uint32_t>> OnWindowResize;
		Ref <Event<uint8_t, uint8_t>> OnKeyPressed;
		Ref <Event<uint8_t>> OnKeyReleased;
		Ref <Event<uint8_t>> OnKeyTyped;
		Ref <Event<uint8_t>> OnMouseButtonPressed;
		Ref <Event<uint8_t>> OnMouseButtonReleased;
		Ref <Event<float, float>> OnMouseScrolled;
		Ref<Event<uint32_t, uint32_t>> OnMouseMoved;

		virtual void Update() = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual float GetAspectRatio() const = 0;

		virtual void SetVSync(bool isVsync) = 0;
		virtual bool IsVSync() const = 0;

		static Scope<Window> Create(std::string name, uint32_t width, uint32_t height);
	};
}