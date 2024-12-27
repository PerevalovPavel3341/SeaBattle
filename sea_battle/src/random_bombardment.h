#ifndef RANDOM_BOMBARDMENT_H
#define RANDOM_BOMBARDMENT_H

#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"

class RandomBombardment : public Ability {
public:
    bool apply(SeaBattlePlayground& field, ShipManager& manager) override;
    ~RandomBombardment() override = default;
};

#endif