#include <vector>
#include <time.h>
#include "game.h"
#include "game_state.h"

enum CellState {
    EMPTY_CELL = '.',
    UNKNOWN_CELL = '~',
    DAMAGED_SHIP = '1',
    UNDAMAGED_SHIP = '2',
    DESTROYED_SHIP = 'x'
};

void Game::place_ships_randomly(SeaBattlePlayground* field, ShipManager* ships) {
	field->clear_field();
	ships->restore_manager();
	for (int i = 0; i < ships->quantity; ++i) {
		bool placed = false;
		time_t counter = 0;
		while (!placed) {
			srand(static_cast<unsigned int>(time(&counter)));
			int x = rand() % field->width;
			int y = rand() % field->length;
			bool vertical = rand() % 2;

			if((vertical)&&(y + ships->ships[i].length > field->length)) continue;
			else{
				if(x + ships->ships[i].length > field->width) continue;
			}

			try {
				field->place_ship(ships->ships[i], x, y, vertical, i, true);
				placed = true;
			} catch (...) {
				counter++;
				continue;
			}
		}
	}
}

void Game::enemy_turn() {
	int x, y;
	do {
		x = rand() % user_field->width;
		y = rand() % user_field->length;
	} while (user_field->field[x][y].cell_state == EMPTY_CELL ||
				user_field->field[x][y].cell_state == DESTROYED_SHIP);

	std::cout << "Enemy attacks (" << x << ", " << y << ")" << std::endl;
	user_field->attack_cell(x, y);
}

void Game::user_turn() {
	bool attack = enemy_field->attack_cell_with_choice();
	if(attack){
		user_abilities->add_random_ability();
	}
}

bool Game::is_game_over(SeaBattlePlayground& field) {
	for(int i = 0; i < field.length; i++){
		for(int k = 0; k < field.width; k++){
			if(field.field[k][i].cell_state == UNDAMAGED_SHIP || field.field[k][i].cell_state == DAMAGED_SHIP)
				return false;
		}
	}
	return true;
}

Game::Game(SeaBattlePlayground* user_f, SeaBattlePlayground* enemy_f, ShipManager* user_s, ShipManager* enemy_s, AbilityManager* user_a, GameState* game_s){
	round = 1;
	user_field = user_f;
	enemy_field = enemy_f;
	user_ships = user_s;
	enemy_ships = enemy_s;
	user_abilities = user_a;
	game_state = game_s;
	std::cout << "Start of round 1..." << std::endl;
	place_ships_randomly(user_field, user_ships);
	place_ships_randomly(enemy_field, enemy_ships);
}

void Game::load(){
	game_state->load("game.txt");
}

void Game::save(){
	game_state->save("game.txt");
}

void Game::attack(){
	user_turn();
	if (is_game_over(*enemy_field)) {
		std::cout << "You win this round!" << std::endl;
		round++;
		std::cout << "Start of round " << round << "..." << std::endl;
		place_ships_randomly(enemy_field, user_ships);
		return;
	}
	enemy_turn();
	if (is_game_over(*user_field)) {
		std::cout << "You lose the game." << std::endl;
		std::cout << "Start of round 1..." << std::endl;
		round = 1;
		place_ships_randomly(user_field, user_ships);
		place_ships_randomly(enemy_field, user_ships);
	}
}

void Game::use_ability(){
	user_abilities->use_ability(*enemy_field, *enemy_ships);
}

void Game::display_playing_fields(){
	user_field->display_your_playing_field();
	enemy_field->display_playing_field_for_enemy();
}