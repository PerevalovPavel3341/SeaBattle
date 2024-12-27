#include <iostream>
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "double_damage.h"

bool DoubleDamage::apply(SeaBattlePlayground& field, ShipManager& manager){
        int x, y;
        std::cout << "Enter coordinates for double damage attack (x y): ";
        std::cin >> x >> y;

        if(field.attack_cell(x, y)) return true;
        if(field.attack_cell(x, y)) return true;
		return false;
}