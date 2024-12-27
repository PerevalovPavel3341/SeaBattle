#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <fstream>
#include "sea_battle_playground.h"
#include "ability_manager.h"
#include "ship_manager.h"

class GameState {
public:
    SeaBattlePlayground* state_player_field;
    SeaBattlePlayground* state_enemy_field;
    AbilityManager* state_player_ability_manager;
    ShipManager* state_player_ship_manager;
    ShipManager* state_enemy_ship_manager;
    
    GameState(SeaBattlePlayground* player_field, SeaBattlePlayground* enemy_field, AbilityManager* player_ability_manager, ShipManager* player_ship_manager, ShipManager* enemy_ship_manager);
	void save(const std::string& filename);
    void load(const std::string& filename);
	
    friend std::ostream& operator<<(std::ostream& os, GameState& state) {
		os << "Player Field:\n";
		state.state_player_field->display_your_playing_field();

		os << "Enemy Field:\n";
		state.state_enemy_field->display_playing_field_for_enemy();

		return os;
	}

private:
    void save_player_field(std::ofstream& ofs);
    void save_enemy_field(std::ofstream& ofs);
    void load_player_field(std::ifstream& ifs);
    void load_enemy_field(std::ifstream& ifs);
    void save_player_ships(std::ofstream& ofs);
    void save_enemy_ships(std::ofstream& ofs);
    void load_player_ships(std::ifstream& ifs);
    void load_enemy_ships(std::ifstream& ifs);
    void load_player_abilities(std::ifstream& ifs);
};

#endif