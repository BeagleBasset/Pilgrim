
#include "States/GameStates/MenuGameState.hpp"
#include <stb_easy_font.h>
#include "Game.hpp"
#include <iostream>


//--------------------------------------
// MenuGameState - Member Functions
//--------------------------------------

void MenuGameState::Update(float dt, Renderer& renderer) {
	// Update menu logic here
}

void MenuGameState::Render(Renderer& renderer) {
    
    renderer.Setup2D();
    const char* text = "Pilgrim - Press Enter to Play";
    char buffer[9999];

    auto [width, height] = renderer.GetWindowSize();
    float scale = 4.0f;

    int text_width = static_cast<int>(strlen(text)) * 8 * scale;

    float x = (width / scale - text_width / scale) + 40 / 2.0f; 
    float y = (height / scale) / 2.0f;

    int num_quads = stb_easy_font_print(x, y, (char*)text, NULL, buffer, sizeof(buffer));

    glPushMatrix();
    glScalef(scale, scale, 1.0f);

    glColor3f(1, 1, 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 16, buffer);
    glDrawArrays(GL_QUADS, 0, num_quads * 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
}

void MenuGameState::HandleInput(Renderer& renderer) {
	// Handle menu input here
	static bool enterPressedLastFrame = false;

	auto window = renderer.GetWindow().get();
	bool enterPressed = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;

	if (enterPressed && !enterPressedLastFrame) {
		std::cout << "ENTER detected, switching to Playing state..." << std::endl;
		Game::GetInstance().ChangeState(GAME_STATE_PLAYING);
	}

    if ((renderer.WindowShouldClose()) || (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)) {
        Game::GetInstance().Quit();
    }

	enterPressedLastFrame = enterPressed;
}

void MenuGameState::Enter(Renderer& renderer) {
	// Code to execute when entering the menu state
	std::cout << "Entering MenuGameState..." << std::endl;
	renderer.Setup2D();
}

void MenuGameState::Exit() {
	// Code to execute when exiting the menu state
	std::cout << "Exiting MenuGameState..." << std::endl;
}