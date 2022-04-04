//
// Created by Cedric on 2022-04-03.
//

#ifndef LD50_COMMON_TURRETMENU_H
#define LD50_COMMON_TURRETMENU_H

#include "UI/Menu.h"
class TurretMenu  : public Menu {

private:
    sf::Sprite turretMenu;

public:
    TurretMenu(const wiz::AssetLoader &assetLoader, Forest &forest);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
};


#endif //LD50_COMMON_TURRETMENU_H
