//
// Created by root on 2022-04-04.
//

#include "UI/PopUp.h"
#include "GameAssets.h"

PopUp::PopUp(const wiz::AssetLoader& assetLoader) {
    popUpText.setCharacterSize(40);
    popUpText.setFillColor(sf::Color::White);
    popUpText.setFont(*assetLoader.get(GameAssets::DEFAULT_FONT));
}

void PopUp::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if (timeLeft > 0)
        target.draw(popUpText);
}

void PopUp::popUp(std::string text, int popUpTime) {
    popUpText.setString(text);
    sf::FloatRect bounds = popUpText.getLocalBounds();
    popUpText.setPosition({(float) 800 - (bounds.width / 2), (float) 900 - bounds.height - 25});
    timeLeft = popUpTime;
}

void PopUp::tick(float delta) {
    timeLeft -= delta;
}
