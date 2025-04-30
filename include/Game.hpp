#pragma once

//--------------------------------------
//✝JMJ✝
// 
// Game Class
//
// DESCRIPTION:
//
// This class is responsible for managing the game state, including the game loop,
// handling input, updating the game world, and rendering the game.
// It is a singleton class, meaning there is only one instance of it throughout the program.
// 
//
// DATE: 2025-04-28
//
//---------------------------------------

#include "States/GameStates/GameState.hpp"
#include "States/GameStates/GameStatesFactory.hpp"
#include "Renderer.hpp"
#include <memory>
#include <string>


class Game {
	public:
		static Game& GetInstance();
		void Init();
		void Run();
		void ChangeState(GameStates newState);
		float GetDeltaTime();
		void Quit();

		bool pPressedLastFrame = false;
	private:
		//----------------------
		//Functions
		//----------------------
		Game() = default;
		~Game() = default;
		Game(const Game&) = delete;
		Game& operator=(const Game&) = delete;
		float CalculateDeltaTime();


		//----------------------
		// Variables
		//----------------------
		bool m_isRunning = false;
		float m_dt = 0.0f;
		float m_lastTime = 0.0f;
		int m_width = 1024;
		int m_height = 768;
		const std::string c_title = "Pilgrim";
		std::unique_ptr<GameState> m_currentState;
		Renderer m_renderer;

}; 

