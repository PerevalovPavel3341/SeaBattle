#include <iostream>
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"
#include "scanner.h"

enum CellState {
    EMPTY_CELL = '.',
    UNKNOWN_CELL = '~',
    DAMAGED_SHIP = '1',
    UNDAMAGED_SHIP = '2',
    DESTROYED_SHIP = 'x'
};


bool Scanner::apply(SeaBattlePlayground& field, ShipManager& manager){
	std::cout << "Enter coordinates for scan (x y): ";
	int x, y;
	std::cin >> x >> y;
	for(int i = x; i < x + 2; ++i) {
		for(int j = y; j < y + 2; ++j) {
			if(field.point_exists(i, j) && field.field[i][j].cell_state == UNDAMAGED_SHIP) {
				std::cout << "Ship segment detected at (" << i << ", " << j << ")" << std::endl;
			}
		}
	}
	return false;
}