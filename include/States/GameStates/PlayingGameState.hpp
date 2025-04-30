#pragma once

//--------------------------------------
//✝JMJ✝
//
// PlayingGameState Class
//
// DESCRIPTION:
//
// This class represents the playing state of the game.
// It inherits from the GameState interface and implements the methods for handling
// the playing state.
// 
// DATE: 2025-04-28
//
//---------------------------------------

#include "GameState.hpp"
#include "World/TerrainManager.hpp"
#include "World/CloudManager.hpp"

class PlayingGameState : public GameState {
	public:
		PlayingGameState() = default;
		~PlayingGameState() override = default;
		void Update(float dt, Renderer& renderer) override;
		void Render(Renderer& renderer) override;
		void HandleInput(Renderer& renderer) override;
		void Enter(Renderer& renderer) override;
		void Exit() override;
	private:
		float m_playerX = 0.0f, m_playerY = 0.0f, m_playerZ = 0.0f, m_moveSpeed = 0.00000005f;
		int chunkSize = 32;
		int renderDistance = 2;
		TerrainManager m_terrainManager{ chunkSize, renderDistance };
		CloudManager m_cloudManager;
};