//
// Created by root on 2022-04-02.
//

#ifndef LD50_CLIENT_ICONBUTTON_H
#define LD50_CLIENT_ICONBUTTON_H


#include "Button.h"
#include "WIZ/asset/TextureAsset.h"

class IconButton : public Button {
    sf::Sprite sprite;
    sf::Sprite currencySprite;
    Currency currency;
    sf::Text priceText;
    sf::Text labelText;

public:
    int price;

    IconButton(sf::IntRect rectangle, Forest& forest, std::function<void(Button*)> onClick, const wiz::AssetLoader& assetLoader, const wiz::TextureAsset* textureType, Currency currency, int price);

    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    void tick(float delta);
};


#endif //LD50_CLIENT_ICONBUTTON_H
