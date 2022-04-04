//
// Created by Cedric on 2022-04-03.
//

#ifndef LD50_COMMON_ANIMALMENU_H
#define LD50_COMMON_ANIMALMENU_H

#include "UI/Menu.h"

class AnimalMenu : public Menu {
private:
    sf::Sprite animalMenu;
public:
    AnimalMenu(const wiz::AssetLoader &assetLoader, Forest &forest);

    void tick(float delta) override;

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
};


#endif //LD50_COMMON_ANIMALMENU_H
