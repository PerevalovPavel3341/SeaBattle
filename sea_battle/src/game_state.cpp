#include <vector>
#include <iostream>
#include <typeinfo>
#include "game_state.h"
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability_manager.h"

GameState::GameState(SeaBattlePlayground* player_f, SeaBattlePlayground* enemy_f, AbilityManager* player_ability_m, ShipManager* player_ship_m, ShipManager* enemy_ship_m){
    state_player_field = player_f;
    state_enemy_field = enemy_f;
    state_player_ability_manager = player_ability_m;
	state_player_ship_manager = player_ship_m;
	state_enemy_ship_manager = enemy_ship_m;
}

void GameState::save(const std::string& filename){
	std::ofstream ofs(filename, std::ios::binary);
	if (!ofs.is_open()) {
		throw std::runtime_error("Unable to open file for saving");
	}

	ofs << state_player_field->width << " " << state_player_field->length << "\n";
	save_player_field(ofs);
	save_enemy_field(ofs);

	save_player_ships(ofs);
	save_enemy_ships(ofs);

	ofs << state_player_ability_manager->abilities.size() << "\n";
	for (auto ability : state_player_ability_manager->abilities) {
		ofs << typeid(*ability).name() << "\n";
	}
}

void GameState::load(const std::string& filename) {
	std::ifstream ifs(filename, std::ios::binary);
	if (!ifs.is_open()) {
		throw std::runtime_error("Unable to open file for loading");
	}

	int field_width, field_length;
	ifs >> field_width >> field_length;

	state_player_field->clear_field();
	state_enemy_field->clear_field();

	state_player_ship_manager->restore_manager();
	state_enemy_ship_manager->restore_manager();

	load_player_field(ifs);
	load_enemy_field(ifs);

	load_player_ships(ifs);
	load_enemy_ships(ifs);

	for(int i = 0; i < state_player_field->length; i++){
		for(int k = 0; k < state_player_field->width; k++){
			int ship_index = state_player_field->field[k][i].ship_index;
			if(ship_index != -1){
				state_player_field->tie_the_ship(&state_player_ship_manager->ships[ship_index], k, i);
			}
		}
	}

	for(int i = 0; i < state_enemy_field->length; i++){
		for(int k = 0; k < state_enemy_field->width; k++){
			if(state_enemy_field->field[k][i].ship_index != -1){
				int ship_id = state_enemy_field->field[k][i].ship_index;
				state_enemy_field->tie_the_ship(&state_enemy_ship_manager->ships[ship_id], k, i);
			}
		}
	}

	load_player_abilities(ifs);
}

void GameState::save_player_field(std::ofstream& ofs) {
	for(int i = 0; i < state_player_field->width; i++){
		for(int k = 0; k < state_player_field->length; k++){
			ofs << state_player_field->field[i][k].cell_state << " " << state_player_field->field[i][k].ship_index << " " << state_player_field->field[i][k].vertical_orientation << " ";
		}
		ofs << "\n";
	}
}

void GameState::save_enemy_field(std::ofstream& ofs) {
	for(int i = 0; i < state_enemy_field->width; i++){
		for(int k = 0; k < state_enemy_field->length; k++){
			ofs << state_enemy_field->field[i][k].cell_state << " " << state_enemy_field->field[i][k].ship_index << " " << state_enemy_field->field[i][k].vertical_orientation << " ";
		}
		ofs << "\n";
	}
}

void GameState::load_player_field(std::ifstream& ifs){
	char cell_state;
	int ship_index;
	bool vertical_orientation;
	for(int i = 0; i < state_player_field->width; i++){
		for(int k = 0; k < state_player_field->length; k++){
			ifs >> cell_state >> ship_index >> vertical_orientation;
			state_player_field->field[i][k].cell_state = cell_state;
			state_player_field->field[i][k].ship_index = ship_index;
			state_player_field->field[i][k].vertical_orientation = vertical_orientation;
		}
	}
}

void GameState::load_enemy_field(std::ifstream& ifs){
	for(int i = 0; i < state_enemy_field->width; i++){
		for(int k = 0; k < state_enemy_field->length; k++){
			char cell_state;
			int ship_index;
			bool vertical_orientation;
				ifs >> cell_state >> ship_index >> vertical_orientation;
				state_enemy_field->field[i][k].cell_state = cell_state;
				state_enemy_field->field[i][k].ship_index = ship_index;
				state_enemy_field->field[i][k].vertical_orientation = vertical_orientation;
		}
	}
}

void GameState::save_player_ships(std::ofstream& ofs){
	ofs << state_player_ship_manager->quantity << "\n";

	for(int i = 0; i < state_player_ship_manager->quantity; i++){
		ofs << state_player_ship_manager->ships[i].length << " " << state_player_ship_manager->ships[i].condition << " " << state_player_ship_manager->ships[i].id << " ";
		for(int k = 0; k < state_player_ship_manager->ships[i].length; k++){
			ofs << state_player_ship_manager->ships[i].hp_bar[k] << " ";
		}
		ofs << "\n";
	}
}

void GameState::save_enemy_ships(std::ofstream& ofs){
	ofs << state_enemy_ship_manager->quantity << "\n";

	for(int i = 0; i < state_enemy_ship_manager->quantity; i++){
		ofs << state_enemy_ship_manager->ships[i].length << " " << state_enemy_ship_manager->ships[i].condition << " " << state_enemy_ship_manager->ships[i].id << " ";
		for(int k = 0; k < state_enemy_ship_manager->ships[i].length; k++){
			ofs << state_enemy_ship_manager->ships[i].hp_bar[k] << " ";
		}
		ofs << "\n";
	}
}

void GameState::load_player_ships(std::ifstream& ifs){
	int quantity;
	ifs >> quantity;

	for (int i = 0; i < quantity; ++i) {
		int length;
		std::string condition;
		int ship_id;
		int hp;
		
		ifs >> length >> condition >> ship_id;

		state_player_ship_manager->ships[i].condition = condition;

		for(int k = 0; k < state_player_ship_manager->ships[i].length; k++){
			ifs >> hp;
			state_player_ship_manager->ships[i].hp_bar[k] = hp;
		}
	}
}

void GameState::load_enemy_ships(std::ifstream& ifs){
	int quantity;
	ifs >> quantity;

	for (int i = 0; i < quantity; ++i) {
		int length;
		std::string condition;
		int ship_id;
		ifs >> length >> condition >> ship_id;

		state_enemy_ship_manager->ships[i].condition = condition;

		for(int k = 0; k < state_enemy_ship_manager->ships[i].length; k++){
			ifs >> state_enemy_ship_manager->ships[i].hp_bar[k];
		}
	}
}

void GameState::load_player_abilities(std::ifstream& ifs) {
	int ability_count;
	ifs >> ability_count;

	state_player_ability_manager->delete_abilities();

	for (int i = 0; i < ability_count; ++i) {
		std::string ability_name;
		ifs >> ability_name;

		if (ability_name == typeid(DoubleDamage).name()) {
			state_player_ability_manager->add_double_damage();
		} else if (ability_name == typeid(Scanner).name()) {
			state_player_ability_manager->add_scanner();
		} else if (ability_name == typeid(RandomBombardment).name()) {
			state_player_ability_manager->add_randbomb();
		}
	}
} 