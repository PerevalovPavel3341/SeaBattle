#include <vector>
#include <iostream>
#include <iomanip>
#include "field_cell.h"
#include "ship.h"
#include "ship_manager.h"
#include "ability_manager.h"
#include "sea_battle_playground.h"
#include "exceptions.h"

enum CellState {
    EMPTY_CELL = '.',
    UNKNOWN_CELL = '~',
    DAMAGED_SHIP = '1',
    UNDAMAGED_SHIP = '2',
    DESTROYED_SHIP = 'x'
};

bool SeaBattlePlayground::point_exists(int x, int y){
	if(x < 0 || y < 0) return false;
	if(x >= width || y >= length) return false;
	return true;
}

bool SeaBattlePlayground::collision_check(int x, int y){

	if(field[x][y].cell_state != UNKNOWN_CELL) return true;

	if(point_exists(x+1, y) && field[x+1][y].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x+1, y+1) && field[x+1][y+1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x+1, y-1) && field[x+1][y-1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x, y-1) && field[x][y-1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x, y+1) && field[x][y+1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x-1, y-1) && field[x-1][y-1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x-1, y+1) && field[x-1][y+1].cell_state != UNKNOWN_CELL) return true;
	if(point_exists(x-1, y) && field[x-1][y].cell_state != UNKNOWN_CELL) return true;

	return false;
}

SeaBattlePlayground::SeaBattlePlayground(){}

SeaBattlePlayground::SeaBattlePlayground(int field_width, int field_length){
	if(field_length <= 0 || field_width <= 0) throw "Incorrect field sizes";

	length = field_length;
	width = field_width;

	std::vector<FieldCell> length_vector(length);

	for(int i = 0; i < width; i++){
		field.push_back(length_vector);
	}
}

SeaBattlePlayground::SeaBattlePlayground(const SeaBattlePlayground& field_to_be_copied){
	length = field_to_be_copied.length;
	width = field_to_be_copied.width;

	field.resize(width);

	for (int i = 0; i < width; i++) {
		field[i].resize(length);

		for (int j = 0; j < length; j++) {
			field[i][j] = field_to_be_copied.field[i][j];

			if (field_to_be_copied.field[i][j].ship != nullptr) {
				field[i][j].ship = new Ship(*field_to_be_copied.field[i][j].ship);
			}
		}
	}
}

SeaBattlePlayground::SeaBattlePlayground(SeaBattlePlayground&& field_for_moving) noexcept {
	length = field_for_moving.length;
	width = field_for_moving.width;
	field = std::move(field_for_moving.field);

	field_for_moving.length = 0;
	field_for_moving.width = 0;
	field_for_moving.field.clear();
}

SeaBattlePlayground& SeaBattlePlayground::operator=(const SeaBattlePlayground& other){
	if (this == &other) return *this;

	for (int i = 0; i < width; i++){
		for (int j = 0; j < length; j++){
			delete field[i][j].ship;
		}
	}

	length = other.length;
	width = other.width;

	field.resize(width);
	for (int i = 0; i < width; i++) {
		field[i].resize(length);
		for (int j = 0; j < length; j++) {
			field[i][j] = other.field[i][j];
			if (other.field[i][j].ship != nullptr){
				field[i][j].ship = new Ship(*other.field[i][j].ship);
			}
		}
	}

	return *this;
}

SeaBattlePlayground& SeaBattlePlayground::operator=(SeaBattlePlayground&& other) noexcept {
	if (this == &other) return *this;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			delete field[i][j].ship;
		}
	}

	length = other.length;
	width = other.width;
	field = std::move(other.field);

	other.length = 0;
	other.width = 0;
	other.field.clear();

	return *this;
}

void SeaBattlePlayground::place_ship(Ship &ship, int x, int y, bool vertical_orientation, int ship_id, bool init){ 
	if(point_exists(x, y) == false){
		throw "Incorrect coordinates";
	}


	if(vertical_orientation){
		if(y + ship.length > length) throw "The ship does not fit on the field";

		for(int i = 0; i < ship.length; i++){
			if(init) {
				if(collision_check(x, y + i)) throw "Collision error";
			}
		}

		field[x][y].vertical_orientation = vertical_orientation;

		for(int i = 0; i < ship.length; i++){
			field[x][y + i].add_ship(&ship, i, true, ship_id);
			if(ship.hp_bar[i] == 2) field[x][y + i].cell_state = UNDAMAGED_SHIP;
			if(ship.hp_bar[i] == 1) field[x][y + i].cell_state = DAMAGED_SHIP;
			if(ship.hp_bar[i] == 0) field[x][y + i].cell_state = DESTROYED_SHIP;
		}
	} else {
		if(x + ship.length > width) throw "The ship does not fit on the field";

		for(int i = 0; i < ship.length; i++){
			if(init){
				if(collision_check(x + i, y)) throw "Collision error";
			}
		}

		field[x][y].vertical_orientation = vertical_orientation;

		for(int i = 0; i < ship.length; i++){
			field[x + i][y].add_ship(&ship, i, false, ship_id);
			if(ship.hp_bar[i] == 2) field[x + i][y].cell_state = UNDAMAGED_SHIP;
			if(ship.hp_bar[i] == 1) field[x + i][y].cell_state = DAMAGED_SHIP;
			if(ship.hp_bar[i] == 0) field[x + i][y].cell_state = DESTROYED_SHIP;
		}
	}
}

bool SeaBattlePlayground::attack_cell_with_choice(){
	std::cout << "Enter coordinates for attack (x y): ";
	int x, y;
    std::cin >> x >> y;
	if(point_exists(x, y) == false){
		throw OutOfBoundsException();
		return false;
	}
	if(field[x][y].cell_state == UNKNOWN_CELL){
		field[x][y].cell_state = EMPTY_CELL;
		std::cout << "Missed" << std::endl;
	}
	else if(field[x][y].cell_state == EMPTY_CELL){
		std::cout << "You cannot attack this cell, choose another one" << std::endl;
		return false;
	}

	if(field[x][y].cell_state == UNDAMAGED_SHIP){
		field[x][y].cell_state = DAMAGED_SHIP;
		field[x][y].ship->damage_the_ship(field[x][y].ship_part_index);
		std::cout << "The segment of the ship is damaged" << std::endl;
	}
	else if(field[x][y].cell_state == DAMAGED_SHIP){
		field[x][y].cell_state = DESTROYED_SHIP;
		field[x][y].ship->damage_the_ship(field[x][y].ship_part_index);
		std::cout << "The segment of the ship is destroyed" << std::endl;
		if(field[x][y].ship->condition == "destroyed"){
			std::cout << "The ship is destroyed" << std::endl;
			reveal_area(x, y);
			return true;
		}
	}
	else if(field[x][y].cell_state == DESTROYED_SHIP){
		std::cout << "You cannot attack this cell, choose another one" << std::endl;
		return false;
	}

	return false;
}

bool SeaBattlePlayground::attack_cell(int x, int y){
	if(point_exists(x, y) == false){
		throw OutOfBoundsException();
		return false;
	}
	if(field[x][y].cell_state == UNKNOWN_CELL){
		field[x][y].cell_state = EMPTY_CELL;
		std::cout << "Missed" << std::endl;
	}
	else if(field[x][y].cell_state == EMPTY_CELL){
		std::cout << "You cannot attack this cell, choose another one" << std::endl;
		return false;
	}

	if(field[x][y].cell_state == UNDAMAGED_SHIP){
		field[x][y].cell_state = DAMAGED_SHIP;
		field[x][y].ship->damage_the_ship(field[x][y].ship_part_index);
		std::cout << "The segment of the ship is damaged" << std::endl;
	}
	else if(field[x][y].cell_state == DAMAGED_SHIP){
		field[x][y].cell_state = DESTROYED_SHIP;
		field[x][y].ship->damage_the_ship(field[x][y].ship_part_index);
		std::cout << "The segment of the ship is destroyed" << std::endl;
		if(field[x][y].ship->condition == "destroyed"){
			std::cout << "The ship is destroyed" << std::endl;
			reveal_area(x, y);
			return true;
		}
	}
	else if(field[x][y].cell_state == DESTROYED_SHIP){
		std::cout << "You cannot attack this cell, choose another one" << std::endl;
		return false;
	}

	return false;
}

void SeaBattlePlayground::fill_with_empty_cells(int x, int y){
	if(point_exists(x+1, y) && field[x+1][y].cell_state != DESTROYED_SHIP) field[x+1][y].cell_state = EMPTY_CELL;
	if(point_exists(x+1, y+1) && field[x+1][y+1].cell_state != DESTROYED_SHIP) field[x+1][y+1].cell_state = EMPTY_CELL;
	if(point_exists(x+1, y-1) && field[x+1][y-1].cell_state != DESTROYED_SHIP) field[x+1][y-1].cell_state = EMPTY_CELL;
	if(point_exists(x, y-1) && field[x][y-1].cell_state != DESTROYED_SHIP) field[x][y-1].cell_state = EMPTY_CELL;
	if(point_exists(x, y+1) && field[x][y+1].cell_state != DESTROYED_SHIP) field[x][y+1].cell_state = EMPTY_CELL;
	if(point_exists(x-1, y-1) && field[x-1][y-1].cell_state != DESTROYED_SHIP) field[x-1][y-1].cell_state = EMPTY_CELL;
	if(point_exists(x-1, y+1) && field[x-1][y+1].cell_state != DESTROYED_SHIP) field[x-1][y+1].cell_state = EMPTY_CELL;
	if(point_exists(x-1, y) && field[x-1][y].cell_state != DESTROYED_SHIP) field[x-1][y].cell_state = EMPTY_CELL;
}

void SeaBattlePlayground::reveal_area(int x, int y){
	if(field[x][y].vertical_orientation){
		while(point_exists(x, y) && field[x][y].ship_part_index != 0){
			y--;
		}

		while(point_exists(x, y) && field[x][y].ship_part_index != -1){
			fill_with_empty_cells(x, y);
			y++;
		}
	} else{
		while(point_exists(x, y) && field[x][y].ship_part_index != 0){
			x--;
		}

		while(point_exists(x, y) && field[x][y].ship_part_index != -1){
			fill_with_empty_cells(x, y);
			x++;
		}
	}
}

void SeaBattlePlayground::clear_field(){
	for(int i = 0; i < width; i++){
		for(int k = 0; k < length; k++){
				field[i][k].cell_state = UNKNOWN_CELL;
				field[i][k].ship = nullptr;
				field[i][k].ship_part_index = -1;
				field[i][k].ship_index = -1;
				field[i][k].vertical_orientation = false;
		}
	}
}

void SeaBattlePlayground::tie_the_ship(Ship* ship, int x, int y){
	if(field[x][y].vertical_orientation){
		for(int i = 0; i < ship->length; i++){
			field[x][y+i].ship = ship;
			field[x][y+i].ship_part_index = i;
		}
	} else{
		for(int i = 0; i < ship->length; i++){
			field[x+i][y].ship = ship;
			field[x+i][y].ship_part_index = i;
		}
	}
}

void SeaBattlePlayground::display_your_playing_field(){
	std::cout << "Your field:" << std::endl;

	for(int i = 0; i < width; i++){
		std::cout << " " << std::setw(2) << i;
	}

	std::cout << std::endl;

	for(int i = 0; i < length; i++){
		std::cout << i;
		for(int k = 0; k < width; k++){
			std::cout << std::setw(2) << static_cast<char>(field[k][i].cell_state) << " ";
		}
		std::cout << std::endl;
	}
}

void SeaBattlePlayground::display_playing_field_for_enemy(){
	std::cout << "Enemy field:" << std::endl;

	for(int i = 0; i < width; i++){
		std::cout << " " << std::setw(2) << i;
	}

	std::cout << std::endl;
	for(int i = 0; i < length; i++){
		std::cout << i;
		for(int k = 0; k < width; k++){
			if(field[k][i].cell_state == UNDAMAGED_SHIP){
				std::cout << std::setw(2) << static_cast<char>(UNKNOWN_CELL) << " ";
			} else{
				std::cout << std::setw(2) << static_cast<char>(field[k][i].cell_state) << " ";
			}
		}
		std::cout << std::endl;
	}
}