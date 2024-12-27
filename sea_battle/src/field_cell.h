#ifndef FIELD_CELL_H
#define FIELD_CELL_H

#include "ship.h"

class FieldCell{
	public:
		Ship* ship;
		int ship_part_index;
		int ship_index;
		char cell_state;
		bool vertical_orientation;

		FieldCell();
		void add_ship(Ship* new_ship, int index, bool vertical, int ship_id);
};

#endif