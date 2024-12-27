#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"
#include "double_damage.h"
#include "ability_manager.h"
#include "exceptions.h"


AbilityManager::AbilityManager() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	std::default_random_engine engine(std::rand());
	std::shuffle(all_abilities.begin(), all_abilities.end(), engine);

	for (auto ability : all_abilities) {
		abilities.push_back(ability);
	}
}

void AbilityManager::delete_abilities(){
	abilities.clear();
}

void AbilityManager::add_double_damage(){
	abilities.push_back(def_abilities[0]);
}

void AbilityManager::add_scanner(){
	abilities.push_back(def_abilities[1]);
}

void AbilityManager::add_randbomb(){
	abilities.push_back(def_abilities[2]);
}

void AbilityManager::add_random_ability() {
	int random_index = std::rand() % all_abilities.size();
	Ability* new_ability = all_abilities[random_index];
	abilities.push_back(new_ability);
}

void AbilityManager::use_ability(SeaBattlePlayground& field, ShipManager& manager) {
	if (abilities.empty()) {
		throw NoAbilityException();
	}

	Ability* ability = abilities.front();
	abilities.erase(abilities.begin());
	if(ability->apply(field, manager)) add_random_ability();
	delete ability;
}