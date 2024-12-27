#ifndef SCANNER_H
#define SCANNER_H

#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability.h"

class Scanner : public Ability {
public:
    bool apply(SeaBattlePlayground& field, ShipManager& manager) override;
    ~Scanner() override = default;
};

#endif