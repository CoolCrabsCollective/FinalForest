//
// Created by Alexander Winter on 2022-04-01.
//

#include "ForestScreen.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "GameAssets.h"
#include "UI/Button.h"

ForestScreen::ForestScreen(wiz::Game& game)
		: Screen(game), forest(*this, game.getAssets()), menu(game.getAssets(), forest) {
}

void ForestScreen::tick(float delta) {
	forest.tick(delta);
    updateSquirrelCount();
    updateNutCount();
    updateMana();
}

void ForestScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.setView(sf::View({50.0f, 50.0f}, {213.33f, 120.0f}));
    target.draw(forest);
    target.setView(sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));
    target.draw(nutCountText);
    target.draw(nutSprite);
    target.draw(squirrelCountText);
    target.draw(squirrelSprite);
    target.draw(manaText);
    target.draw(manaSprite);
    target.draw(menu);
}

void ForestScreen::show() {
#ifndef OS_SWITCH
    nutTexture = *getGame().getAssets().get(GameAssets::NUT);
    nutSprite.setTexture(nutTexture);
#endif
    nutSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    nutSprite.setColor(sf::Color(255, 255, 255, 200));
    nutSprite.setPosition(sf::Vector2f(1500.0f, 25.0f));
    nutSprite.setScale({2.0f, 2.0f});

#ifndef OS_SWITCH
    squirrelTexture = *getGame().getAssets().get(GameAssets::SQUIRREL);
    squirrelSprite.setTexture(squirrelTexture);
#endif
    squirrelSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    squirrelSprite.setColor(sf::Color(255, 255, 255, 200));
    squirrelSprite.setPosition(sf::Vector2f(1500.0f, 75.0f));
    squirrelSprite.setScale({2.0f, 2.0f});

#ifndef OS_SWITCH
    manaTexture = *getGame().getAssets().get(GameAssets::MANA);
    manaSprite.setTexture(manaTexture);
#endif
    manaSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    manaSprite.setColor(sf::Color(255, 255, 255, 200));
    manaSprite.setPosition(sf::Vector2f(1500.0f, 125.0f));
    manaSprite.setScale({2.0f, 2.0f});

	getGame().addWindowListener(this);

	getGame().addInputListener(this);
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

void ForestScreen::updateNutCount() {
    squirrelCountText.setString(std::to_string(forest.nutCount));
    squirrelCountText.setPosition(sf::Vector2f(1550, 25));
    squirrelCountText.setCharacterSize(20);
    squirrelCountText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
}

void ForestScreen::updateSquirrelCount() {
    nutCountText.setString(std::to_string(forest.squirrelCount));
    nutCountText.setPosition(sf::Vector2f(1550, 75));
    nutCountText.setCharacterSize(20);
    nutCountText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
}

void ForestScreen::updateMana() {
    manaText.setString(std::to_string(forest.mana));
    manaText.setPosition(sf::Vector2f(1550, 125));
    manaText.setCharacterSize(20);
    manaText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));
}

bool ForestScreen::isDebug() const {
	return debug;
}

void ForestScreen::setDebug(bool debug) {
	ForestScreen::debug = debug;
}

void ForestScreen::keyPressed(const sf::Event::KeyEvent& keyEvent) {
	if(keyEvent.code == sf::Keyboard::F12)
		debug = !debug;
}

void ForestScreen::mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) {
    sf::Vector2f clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y), sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));
    menu.click(clickVector);
}
