#include "ZoomApp.h"
#include "meta.generated.hpp"

#include <Fjord/core/EntryPoint.h>

#include "Game.h"

namespace Fjord
{
	Application* CreateApplication()
	{
		return new ZoomApp();
	}

	ZoomApp::ZoomApp()
	{
		m_flows.emplace_back(CreateRef<Game>());
	}

	ZoomApp::~ZoomApp()
	{

	}

	void ZoomApp::UpdateInternal()
	{
	}

}
