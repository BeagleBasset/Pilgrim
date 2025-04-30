#pragma once

//--------------------------------------
//✝JMJ✝
//
// GameStatesFactory Class
//
// DESCRIPTION:
//
// This class is responsible for creating and managing game states.
//
//	
// DATE: 2025-04-28
//
//---------------------------------------

#include <memory>
#include "States/GameStates/GameState.hpp"
#include "States/GameStates/MenuGameState.hpp"
#include "States/GameStates/PlayingGameState.hpp"
#include "States/GameStates/PausedGameState.hpp"
#include "States/GameStates/GameStatesEnum.hpp"

class GameStatesFactory {
	public:
		static std::unique_ptr<GameState> CreateState(GameStates state);
};