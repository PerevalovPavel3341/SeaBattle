#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include "game.h"

template<typename InputProcessor>
class GameController {
public:
    Game* game;
    InputProcessor input_processor;

    GameController(Game* game_instance, InputProcessor processor) : game(game_instance), input_processor(processor) {}
    bool process_command() {
        char command = input_processor.get_command();
        switch (command) {
            case 'a': game->attack(); return true;
            case 's': game->save(); return true;
            case 'l': game->load(); return true;
            case 'u': game->use_ability(); return true;
            case 'q': return false;
            default: std::cout << "Unknown command!" << std::endl;
        }
        return true;
    }
};

#endif
