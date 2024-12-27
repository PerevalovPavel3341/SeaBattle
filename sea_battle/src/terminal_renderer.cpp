#include "terminal_renderer.h"

void TerminalRenderer::render(Game* game) {
	std::cout << "Rendering game field..." << std::endl;
	game->display_playing_fields(); 
}
