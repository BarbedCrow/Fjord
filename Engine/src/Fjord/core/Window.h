#pragma once

#include <string>

#include "Core.h"

namespace Fjord
{
	class Window
	{
	public:
		virtual void Update() = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetVSync(bool isVsync) = 0;
		virtual bool IsVSync() const = 0;

		static Scope<Window> Create(std::string name, uint32_t width, uint32_t height);
	};
}