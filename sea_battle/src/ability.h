#ifndef ABILITY_H
#define ABILITY_H

#include "sea_battle_playground.h"
#include "ship_manager.h"

class Ability {
public:
    virtual bool apply(SeaBattlePlayground& field, ShipManager& manager) = 0;
    virtual ~Ability() = default;
};


#endif