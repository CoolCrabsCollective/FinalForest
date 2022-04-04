//
// Created by root on 2022-04-04.
//

#ifndef LD50_CLIENT_POPUP_H
#define LD50_CLIENT_POPUP_H


#include <string>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "world/Tickable.h"

class PopUp : public sf::Drawable, public Tickable {
    sf::Text popUpText;
    float timeLeft = 0.0f; // MS

public:
    PopUp(const wiz::AssetLoader& assetLoader);

    void popUp(std::string text, int popUpTime); // popUpTime is in milli seconds

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void tick(float delta) override;
};


#endif //LD50_CLIENT_POPUP_H
