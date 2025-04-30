#pragma once

//--------------------------------------
//✝JMJ✝
// 
// GameState Interface
//
// DESCRIPTION:
// 
// This interface defines the basic structure for game states in the game engine.
// It includes methods for entering, updating, rendering, and exiting the game state.
// Each game state should implement this interface to define its specific behavior.
//
// DATE: 2025-04-28
//
//---------------------------------------

#include "Renderer.hpp"


class GameState {
	public:
		virtual ~GameState() = default;
		virtual void Update(float dt, Renderer& renderer) = 0;
		virtual void Render(Renderer& renderer) = 0;
		virtual void HandleInput(Renderer& renderer) = 0;
		virtual void Enter(Renderer& renderer) = 0;
		virtual void Exit() = 0;
	protected:
		GameState() = default;

};
