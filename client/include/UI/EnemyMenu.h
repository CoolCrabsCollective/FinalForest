//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ENEMYMENU_H
#define LD50_CLIENT_ENEMYMENU_H

#include "Menu.h"

class EnemyMenu : public Menu {
private:
    sf::Sprite enemyMenu;
public:
    EnemyMenu(const wiz::AssetLoader &assetLoader, Forest &forest);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
};

#endif //LD50_CLIENT_ENEMYMENU_H
