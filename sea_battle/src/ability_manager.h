#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include <vector>
#include "ship_manager.h"
#include "ability.h"
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "double_damage.h"
#include "scanner.h"
#include "random_bombardment.h"



class AbilityManager {

public:
    std::vector<Ability*> abilities;
    std::vector<Ability*> def_abilities = {
            new DoubleDamage(),
            new Scanner(),
            new RandomBombardment()
    };
	std::vector<Ability*> all_abilities = {
            new DoubleDamage(),
            new Scanner(),
            new RandomBombardment()
    };

	AbilityManager();

    void delete_abilities();
    void add_random_ability();
    void add_double_damage();
    void add_scanner();
    void add_randbomb();;
    void use_ability(SeaBattlePlayground& field, ShipManager& manager);
};
#endif