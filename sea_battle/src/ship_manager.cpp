#include <vector>
#include "ship.h"
#include "ship_manager.h"

ShipManager::ShipManager(){
	quantity = 0;
};

ShipManager::ShipManager(int ships_quantity, std::vector<int>& ship_sizes){
	if(ships_quantity != ship_sizes.size()){
		throw "Wrong number of ships";
	}

	quantity = ships_quantity;

	for(int i = 0; i < ships_quantity; i++){
		ships.push_back(Ship(ship_sizes[i], i));
	}
}

void ShipManager::add_ship(Ship& new_ship){
	quantity++;
	ships.push_back(std::move(new_ship));
}

Ship& ShipManager::find_ship_by_id(int ship_index){

	if(ship_index < 0 || ship_index >= quantity) throw "Incorrect ship index";
	for(int i = 0; i < quantity; i++){
		if(ships[i].id == ship_index){
			Ship& new_ship = ships[i];
			return new_ship;
		}
	}
	return ships[0];
}

Ship& ShipManager::get_ship(int index) {
	if (index >= 0 && index < quantity) {
		return ships[index];
	} else throw "Incorrect ship index";
}

void ShipManager::restore_manager(){
	for(int i = 0; i < ships.size(); i++){
		ships[i].restore_the_ship();
	}
}