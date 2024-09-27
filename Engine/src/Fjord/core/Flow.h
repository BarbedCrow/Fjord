#pragma once

#include "Fjord/ECS/Systems/GameSystem.h"

/*
 * Main class that you want to extend to create your own
 * flow in the application. Flow means a specific part of
 * the game(e.g. Main menu flow, game flow, mayme some
 * 3d map flow inside the game itself etc.)
 *
 * The flow gives you an opportunity to decide which systems
 * you might want to use in the game and specify an order
 * in which these systems will be activated and updated
 */
namespace Fjord
{
	class Flow
	{
	public:
		Flow() = default;
		virtual ~Flow() = default;

		void Start();
		void Update();
		void Close();

	protected:
		virtual void UpdateInternal() = 0;

	protected:
		std::vector<Ref<GameSystem>> m_systems;
	};
}