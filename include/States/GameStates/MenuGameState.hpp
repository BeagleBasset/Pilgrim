#pragma once

//--------------------------------------
//✝JMJ✝
//
// MenuGameState Class
//
// DESCRIPTION:
//
// This class represents the menu state of the game.
// It inherits from the GameState interface and implements the methods for handling
// the menu state.
//
// DATE: 2025-04-28
//
//---------------------------------------

#include "GameState.hpp"


class MenuGameState : public GameState {
	public:
		MenuGameState() = default;
		~MenuGameState() override = default;
		void Update(float dt, Renderer& renderer) override;
		void Render(Renderer& renderer) override;
		void HandleInput(Renderer& renderer) override;
		void Enter(Renderer& renderer) override;
		void Exit() override;
};