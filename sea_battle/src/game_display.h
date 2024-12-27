#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include <iostream>
#include "game.h"

template<typename Renderer>
class GameDisplay {
public:
    Game* game;
    Renderer renderer;

    GameDisplay(Game* game_instance, Renderer renderer_instance) : game(game_instance), renderer(renderer_instance) {}
    void render() {
        renderer.render(game);
    }
};

#endif
