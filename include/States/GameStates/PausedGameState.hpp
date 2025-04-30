#pragma once

//--------------------------------------
//✝JMJ✝
//
// PausedGameState Class
//
// DESCRIPTION:
//
// This class represents the paused state of the game.
// It inherits from the GameState interface and implements the methods for handling
// the paused state.
// 
// DATE: 2025-04-28
//
//---------------------------------------

#include "GameState.hpp"

class PausedGameState : public GameState {
public:
	PausedGameState() = default;
	~PausedGameState() override = default;
	void Update(float dt, Renderer& renderer) override;
	void Render(Renderer& renderer) override;
	void HandleInput(Renderer& renderer) override;
	void Enter(Renderer& renderer) override;
	void Exit() override;
};