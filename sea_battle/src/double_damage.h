#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"

class DoubleDamage : public Ability {
public:
    bool apply(SeaBattlePlayground& field, ShipManager& manager) override;
    ~DoubleDamage() override = default;
};

#endif