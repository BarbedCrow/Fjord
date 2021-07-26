#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Core.h"

namespace Fjord
{
	class Log
	{
	public:
		Log();
		~Log();

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define FJORD_CORE_ERROR(...)    ::Fjord::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FJORD_CORE_WARNING(...)  ::Fjord::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FJORD_CORE_INFO(...)     ::Fjord::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FJORD_CORE_TRACE(...)    ::Fjord::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define FJORD_ERROR(...)    ::Fjord::Log::GetClientLogger()->error(__VA_ARGS__)
#define FJORD_WARNING(...)  ::Fjord::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FJORD_INFO(...)     ::Fjord::Log::GetClientLogger()->info(__VA_ARGS__)
#define FJORD_TRACE(...)    ::Fjord::Log::GetClientLogger()->trace(__VA_ARGS__)
