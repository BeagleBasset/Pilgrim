#include "Game.hpp"
#include "States/GameStates/MenuGameState.hpp"
#include "States/GameStates/PlayingGameState.hpp"
#include "States/GameStates/PausedGameState.hpp"
#include <iostream>
#include <chrono>


Game& Game::GetInstance()
{
	static Game game;
	return game;
}

void Game::Init()
{
	std::cout << "Init called..." << std::endl;
	m_isRunning = true;
	m_lastTime = static_cast<float>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	m_currentState = GameStatesFactory::CreateState(GAME_STATE_MENU);
	m_renderer = Renderer();
	m_renderer.Init(m_width,m_height,c_title);
}

void Game::Run()
{
	Init();
	while (m_isRunning)
	{
		m_dt = CalculateDeltaTime();
		
		m_renderer.BeginFrame();

		m_currentState->Update(m_dt, m_renderer);
		m_currentState->Render(m_renderer);
		m_currentState->HandleInput(m_renderer);

		m_renderer.EndFrame();

	}
}


float Game::CalculateDeltaTime()
{
	auto currentTime = static_cast<float>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	float deltaTime = currentTime - m_lastTime;
	m_lastTime = currentTime;
	return deltaTime;
}

void Game::ChangeState(GameStates newState)
{
	if (m_currentState) {
		m_currentState->Exit();
	}
	m_currentState = GameStatesFactory::CreateState(newState);
	if (m_currentState) {
		m_currentState->Enter(m_renderer);
	}

}

void Game::Quit()
{
	m_isRunning = false;
	std::cout << "Game is quitting..." << std::endl;
}

float Game::GetDeltaTime()
{
	return m_dt;
}

