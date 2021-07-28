#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include "Fjord/core/Core.h"

namespace Fjord
{

	template <class... Args>
	class Event
	{
	public:

		Event(void* owner) : m_Owner(owner) {}
		~Event() = default;

		void AddListener(void* listener, std::function<bool(Args...)> listenerFunc) 
		{ 
			if (m_Listeners.find(listener) != m_Listeners.end())
			{
				FJORD_CORE_ASSERT(false, "{0} was already subscribed", listener);
				return;
			}

			m_ListenerFuncs.push_back(listenerFunc);
			m_Listeners[listener] = m_ListenerFuncs.size() - 1;
		}

		void RemoveListener(void* listener) 
		{  
			auto res = m_Listeners.find(listener);
			if (res == m_Listeners.end()) return;

			m_ListenerFuncs.erase(m_ListenerFuncs.begin() + res->second);
			m_Listeners.erase(listener);
		}

		void Invoke(void* invoker, Args... args)
		{
			if (m_Owner != invoker) FJORD_CORE_ASSERT(false, "Trying to invoke event from outer class");
			for (auto& listenerFunc : m_ListenerFuncs)
			{
				if (listenerFunc(std::forward<Args>(args)...)) return;
			}
		}
	private:
		void* m_Owner;
		std::vector<std::function<bool(Args...)>> m_ListenerFuncs;
		std::unordered_map<void*, int> m_Listeners;
	};
}