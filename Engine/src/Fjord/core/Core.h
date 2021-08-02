#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define FJORD_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define FJORD_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define FJORD_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define FJORD_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define FJORD_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef FJORD_ENABLE_ASSERTS
#define FJORD_CORE_ASSERT(x) {if(!(x)) {__debugbreak();}}
#define FJORD_ASSERT(x) {if(!(x)) {__debugbreak();}}
#else
#define FJORD_CORE_ASSERT(x)
#define FJORD_ASSERT(x)
#endif

#define BIT(x) (1 << x)

#define BIND_FUNC_0(fn) std::bind(&fn, this)
#define BIND_FUNC_1(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_FUNC_2(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_FUNC_3(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_FUNC_4(fn) std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

#define BIND_EVENT_HANDLER_0(fn) this, std::bind(&fn, this)
#define BIND_EVENT_HANDLER_1(fn) this, std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_HANDLER_2(fn) this, std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2)
#define BIND_EVENT_HANDLER_3(fn) this, std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define BIND_EVENT_HANDLER_4(fn) this, std::bind(&fn, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)

namespace Fjord
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}