#include "fjordpch.h"

#include "Flow.h"

namespace Fjord
{
	void Flow::Start()
	{
		for (auto sys : m_systems)
		{
			sys->Activate();
		}
	}

	void Flow::Update()
	{
		for (auto sys : m_systems)
		{
			if (sys->IsActive()) sys->Update();
		}
	}

	void Flow::Close()
	{
		
	}



}
