#include <vector>
#include <iostream>
#include "ship.h"
#include "field_cell.h"

enum CellState {
    EMPTY_CELL = '.',
    UNKNOWN_CELL = '~',
    DAMAGED_SHIP = '1',
    UNDAMAGED_SHIP = '2',
    DESTROYED_SHIP = 'x'
};

FieldCell::FieldCell(){
	cell_state = UNKNOWN_CELL;
	ship = nullptr;
	ship_part_index = -1;
	ship_index = -1;
	vertical_orientation = false;
}

void FieldCell::add_ship(Ship* new_ship, int index, bool vertical, int ship_id){
	if(index == 0){
		ship_index = ship_id;
	}
	ship = new_ship;
	ship_part_index = index;
	vertical_orientation = vertical;
	cell_state = UNDAMAGED_SHIP;
}