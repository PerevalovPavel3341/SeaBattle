#include <iostream>
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"
#include "random_bombardment.h"

enum CellState {
    EMPTY_CELL = '.',
    UNKNOWN_CELL = '~',
    DAMAGED_SHIP = '1',
    UNDAMAGED_SHIP = '2',
    DESTROYED_SHIP = 'x'
};


bool RandomBombardment::apply(SeaBattlePlayground& field, ShipManager& manager){
	int ship_index = rand() % manager.quantity;
	Ship& target_ship = manager.get_ship(ship_index);
	int segment = rand() % target_ship.length;

	for (int x = 0; x < field.width; x++) {
		for (int y = 0; y < field.length; y++) {
			FieldCell& cell = field.field[x][y];
			if (cell.cell_state == UNDAMAGED_SHIP || cell.cell_state == DAMAGED_SHIP) {
				std::cout << "Random bombardment applied to ship " << ship_index
							<< " at coordinates (" << x << ", " << y << ")" << std::endl;
				return(field.attack_cell(x, y));
			}
		}
	}

	throw std::runtime_error("Segment not found on the field");
}