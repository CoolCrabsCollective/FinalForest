//
// Created by Winter on 12/02/2022.
//

#include <ForestScreen.h>

#include <memory>
#include "LoadingScreen.h"
#include "TitleScreen.h"
#include "GameAssets.h"

LoadingScreen::LoadingScreen(wiz::Game& game)
	: Screen(game) {}

void LoadingScreen::tick(float delta) {
	getGame().getAssets().update(16.0f);

	if(getGame().getAssets().isAllLoaded())
		getGame().setScreen(std::make_shared<ForestScreen>(getGame()));
}

void LoadingScreen::render(sf::RenderTarget& target) {

	target.clear(sf::Color(0, 0, 0, 255));

	float width = target.getView().getSize().x * 0.5f;
	float y = target.getView().getSize().y * 3.0f / 4.0f;

	sprite.setColor(sf::Color(128, 128, 128, 255));
	sprite.setPosition(sf::Vector2(target.getView().getCenter().x - width / 2.0f, y));
	sprite.setScale(sf::Vector2(width, 1.0f));
	target.draw(sprite);

	sprite.setColor(sf::Color(255, 255, 255, 255));
	sprite.setPosition(sf::Vector2(target.getView().getCenter().x - width / 2.0f, y));
	sprite.setScale(sf::Vector2(width * getAssets().getProgress(), 1.0f));
	target.draw(sprite);

	sf::FloatRect rect = message.getLocalBounds();

	message.setPosition(sf::Vector2f(target.getView().getCenter().x - rect.getSize().x / 2.0f,
						target.getView().getSize().y / 4.0f));
	target.draw(message);
}

void LoadingScreen::show() {

	getGame().getAssets().loadAll(GameAssets::ALL);
	getGame().getAssets().finishLoading(GameAssets::DEFAULT_FONT);
	getGame().getAssets().finishLoading(GameAssets::WHITE_PIXEL);
	getGame().getAssets().finishLoading(GameAssets::TREE_TURRET);

	sprite.setTexture(*getGame().getAssets().get(GameAssets::WHITE_PIXEL));

	message.setString("Loading...");
	message.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

	sf::Texture* iconTex = getGame().getAssets().get(GameAssets::TREE_TURRET);
#ifndef OS_SWITCH
	sf::Image image = iconTex->copyToImage();
	getWindow().setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
#endif

	getGame().addWindowListener(this);
}

void LoadingScreen::hide() {
	getGame().removeWindowListener(this);
}

const std::string& LoadingScreen::getName() const {
	return name;
}

void LoadingScreen::windowClosed() {
	getGame().getWindow().close();
}
