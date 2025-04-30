#include "States/GameStates/GameStatesFactory.hpp"

std::unique_ptr<GameState> GameStatesFactory::CreateState(GameStates state)
{
    switch (state) {
    case GAME_STATE_MENU:
        return std::make_unique<MenuGameState>();
    case GAME_STATE_PLAYING:
        return std::make_unique<PlayingGameState>();
    case GAME_STATE_PAUSED:
        return std::make_unique<PausedGameState>();
    default:
        return nullptr;
    }
}