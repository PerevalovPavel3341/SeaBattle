#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <vector>
#include "ship.h"

class ShipManager{
	public:
		std::vector<Ship> ships;
		int quantity;

		ShipManager();
		ShipManager(int ships_quantity, std::vector<int>& ship_sizes);
		void add_ship(Ship& new_ship);
		void restore_manager();
		Ship& find_ship_by_id(int ship_index);
		Ship& get_ship(int index);
};

#endif