//------------------------
// Pilgrim - Entry Point
//------------------------

#include "Game.hpp"

int main() {

	Game& game = Game::GetInstance();
	game.Run();
    return 0;

}
    