//
// Created by root on 2022-04-02.
//

#ifndef LD50_CLIENT_MENU_H
#define LD50_CLIENT_MENU_H


#include "SFML/Graphics/Drawable.hpp"
#include "Button.h"

class Menu : public sf::Drawable {
    std::vector<Button*> buttons;
    const wiz::AssetLoader& assetLoader;
    sf::Sprite sprite;

public:
    Menu(const wiz::AssetLoader& assetLoader);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD50_CLIENT_MENU_H
