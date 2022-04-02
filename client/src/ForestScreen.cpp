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
}

void ForestScreen::show() {
    nutCountText.setString("0");
    nutCountText.setPosition(sf::Vector2f(1550, 0));
    nutCountText.setCharacterSize(20);
    nutCountText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));

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
