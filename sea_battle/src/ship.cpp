#include <iostream>
#include <vector>
#include "ship.h"

Ship::Ship(int ship_length, int ship_index){
	if(ship_length > 4 || ship_length < 1) throw "Incorrect ship length";
	length = ship_length;
	id = ship_index;
	condition = intact;
	hp_bar.resize(length);

	std::fill(hp_bar.begin(), hp_bar.end(), 2);
}

void Ship::damage_the_ship(int ship_part_index){
	if(ship_part_index < 0 || ship_part_index >= length){
		std::cout << length << std::endl;
		std::cout << ship_part_index << std::endl; 
		throw "Index out of range";
	}

	condition = damaged;

	if(hp_bar[ship_part_index] != 0) hp_bar[ship_part_index]--;

	bool ship_was_destroyed = true;

	for(int i = 0; i < length; i++){
		if(hp_bar[i] != 0){
			ship_was_destroyed = false;
			break;
		}
	}

	if(ship_was_destroyed) condition = destroyed;
}

void Ship::restore_the_ship(){
	condition = intact;
	for(int i = 0; i < length; i++){
		hp_bar[i] = 2;
	}
}