//
// Created by Alexander Winter on 2022-04-01.
//

#include "ForestScreen.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "GameAssets.h"

ForestScreen::ForestScreen(wiz::Game& game)
		: Screen(game), forest(game.getAssets()) {
}

void ForestScreen::tick(float delta) {
	forest.tick(delta);
}

void ForestScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.setView(sf::View({50.0f, 50.0f}, {213.33f, 120.0f}));
    target.draw(forest);
    target.setView(sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));
    target.draw(nutCountText);
    target.draw(nutSprite);
}

void ForestScreen::show() {
    nutCountText.setString("0");
    nutCountText.setPosition(sf::Vector2f(1550, 25));
    nutCountText.setCharacterSize(20);
    nutCountText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));

    nutTexture = *getGame().getAssets().get(GameAssets::NUT);
    nutSprite.setTexture(nutTexture);
    nutSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    nutSprite.setColor(sf::Color(255, 255, 255, 200));
    nutSprite.setPosition(sf::Vector2f(1500.0f, 25.0f));
    nutSprite.setScale({2.0f, 2.0f});

	getGame().addWindowListener(this);
}

void ForestScreen::hide() {
	getGame().removeWindowListener(this);
}

const std::string& ForestScreen::getName() const {
	return name;
}

void ForestScreen::windowClosed() {
	getGame().getWindow().close();
}
