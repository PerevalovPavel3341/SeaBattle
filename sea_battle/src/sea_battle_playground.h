#ifndef SEA_BATTLE_PLAYGROUND_H
#define SEA_BATTLE_PLAYGROUND_H

#include <vector>
#include <iostream>
#include "field_cell.h"
#include "ship.h"
#include "ship_manager.h"

class AbilityManager;

class SeaBattlePlayground{
	private:
		bool collision_check(int x, int y);

	public:
		std::vector<std::vector<FieldCell>> field;
		int length;
		int width;

		SeaBattlePlayground();
		SeaBattlePlayground(int field_width, int field_length);
		SeaBattlePlayground(const SeaBattlePlayground& field_to_be_copied);
		SeaBattlePlayground(SeaBattlePlayground&& field_for_moving) noexcept;

		SeaBattlePlayground& operator=(const SeaBattlePlayground& other);
    	SeaBattlePlayground& operator=(SeaBattlePlayground&& other) noexcept;

		bool point_exists(int x, int y);
		void place_ship(Ship &ship, int x, int y, bool vertical_orientation, int ship_id, bool init);
		bool attack_cell_with_choice();
		bool attack_cell(int x, int y);
		void fill_with_empty_cells(int x, int y);
		void reveal_area(int x, int y);
		void clear_field();
		void tie_the_ship(Ship* ship, int x, int y);
		void display_your_playing_field();
		void display_playing_field_for_enemy();
};

#endif