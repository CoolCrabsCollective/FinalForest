//
// Created by Alexander Winter on 2022-04-01.
//

#ifndef WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H
#define WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H

#include "WIZ/game/Screen.h"
#include "WIZ/game/WindowListener.h"
#include "Box2D/Dynamics/b2World.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "world/Forest.h"
#include "SFML/Graphics/Texture.hpp"

class ForestScreen : public wiz::Screen, public wiz::WindowListener {
	std::string name = "ForestScreen";

    sf::Text nutCountText;
    sf::Texture nutTexture;
    sf::Sprite nutSprite;
    sf::Text squirrelCountText;
    sf::Texture squirrelTexture;
    sf::Sprite squirrelSprite;
    sf::Text manaText;
    sf::Texture manaTexture;
    sf::Sprite manaSprite;

	Forest forest;

public:
	ForestScreen(wiz::Game& game);

	void tick(float delta) override;

	void render(sf::RenderTarget& target) override;

	void show() override;

	void hide() override;

	const std::string& getName() const override;

	void windowClosed() override;

    void updateNutCount();

    void updateSquirrelCount();

    void updateMana();
};


#endif //WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H
