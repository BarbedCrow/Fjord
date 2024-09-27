#pragma once

#include <Fjord.h>

namespace Fjord
{
	class Game;
	class ZoomApp : public Application
	{
	public:
			ZoomApp();
			~ZoomApp() override;

	protected:
			void UpdateInternal() override;
	};
}
