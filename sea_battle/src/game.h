#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability_manager.h"
#include "ship.h"
#include "exceptions.h"
#include "game_state.h"

class Game {
private:
    SeaBattlePlayground* user_field;
    SeaBattlePlayground* enemy_field;
    ShipManager* user_ships;
    ShipManager* enemy_ships;
    AbilityManager* user_abilities;
    GameState* game_state;
    int round;

    void initialize_fields();
    void place_ships_randomly(SeaBattlePlayground* field, ShipManager* ships);
    void enemy_turn();
    void user_turn();
    bool is_game_over(SeaBattlePlayground& field);
public:
    Game(SeaBattlePlayground* user_field, SeaBattlePlayground* enemy_field, ShipManager* user_ships, ShipManager* enemy_ships, AbilityManager* user_abilities, GameState* game_state);
    void load();
    void save();
    void attack();
    void use_ability();
    void display_playing_fields();
};

#endif