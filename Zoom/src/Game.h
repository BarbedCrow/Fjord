#pragma once

#include "Fjord.h"

namespace Fjord
{
	class Game : public Flow
	{
	public:
		Game();
		~Game() override;

		Ref<Scene> GetScene() { return m_scene; }

	protected:
		void UpdateInternal() override;

	private:
		Ref<Scene> m_scene;
	};
}