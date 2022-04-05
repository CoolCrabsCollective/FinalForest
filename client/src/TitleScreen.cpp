//
// Created by Alexander Winter🤤 on 2022-03-12.
//

#include "TitleScreen.h"

#include <memory>
#include "GameAssets.h"
#include "SFML/Window/Touch.hpp"
#include "ForestScreen.h"

TitleScreen::TitleScreen(wiz::Game& game)
	: Screen(game) {

	logo.setTexture(*getAssets().get(GameAssets::LOGO));
	background.setTexture(*getAssets().get(GameAssets::GRASS));

	playWithMouse.setFont(*getAssets().get(GameAssets::DEFAULT_FONT));
	clickToPlay.setFont(*getAssets().get(GameAssets::DEFAULT_FONT));

	playWithMouse.setString("Play with Mouse or Touchscreen");
	clickToPlay.setString("Click to start!");
	playWithMouse.setCharacterSize(50);
	clickToPlay.setCharacterSize(50);

#ifndef OS_SWITCH
	sf::FloatRect bounds = playWithMouse.getLocalBounds();
	playWithMouse.setPosition(sf::Vector2f(game.getWindow().getView().getSize().x / 2.0f - bounds.getSize().x / 2,
										   game.getWindow().getView().getSize().y / 2.0f - bounds.getSize().y / 2));

	sf::FloatRect bounds2 = clickToPlay.getLocalBounds();
	clickToPlay.setPosition(sf::Vector2f(game.getWindow().getView().getSize().x / 2.0f - bounds2.getSize().x / 2,
										   game.getWindow().getView().getSize().y * 3.0f / 4.0f - bounds2.getSize().y / 2));
#endif

	click.setBuffer(*getAssets().get(GameAssets::CLICK_SOUND));
	click.setVolume(100.0f);
}

void TitleScreen::tick(float delta) {
	sf::Vector2f vec(getGame().getWindow().getView().getSize());

	logo.setOrigin(sf::Vector2f(logo.getTextureRect().getSize() / 2));
	logo.setPosition({vec.x / 2.0f, vec.y / 4.0f});
	logo.setScale(sf::Vector2f(6.0f, 6.0f));

	vec.x /= static_cast<float>(background.getTextureRect().getSize().x);
	vec.y /= static_cast<float>(background.getTextureRect().getSize().y);
	background.setScale(vec);

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i pos = sf::Mouse::getPosition(getWindow());

		if(pos.x >= 0 && pos.y >= 0 && pos.x <= getWindow().getSize().x && pos.y <= getWindow().getSize().y) {

			click.play();
			getGame().setScreen(std::make_shared<ForestScreen>(getGame()));
			return;
		}
	}

	if(sf::Touch::isDown(1)) {
		sf::Vector2i pos = sf::Touch::getPosition(1, getWindow());

		if(pos.x >= 0 && pos.y >= 0 && pos.x <= getWindow().getSize().x && pos.y <= getWindow().getSize().y) {

			click.play();
			getGame().setScreen(std::make_shared<ForestScreen>(getGame()));
			return;
		}
	}
}

void TitleScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.draw(background);
	target.draw(logo);
#ifndef OS_SWITCH
	target.draw(playWithMouse);
	target.draw(clickToPlay);
#endif
}

void TitleScreen::show() {

	getGame().addWindowListener(this);

	int i;
	for(i = 0; true; i++) {
		if(!sf::Joystick::isConnected(i))
			break;

		sf::Joystick::Identification id = sf::Joystick::getIdentification(i);
		unsigned int buttonCount = sf::Joystick::getButtonCount(i);

		std::stringstream ss;

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::X))
			ss << "X";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::Y))
			ss << "Y";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::U))
			ss << "U";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::V))
			ss << "V";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::Z))
			ss << "Z";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::R))
			ss << "R";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::PovX))
			ss << "pX";

		if(sf::Joystick::hasAxis(i, sf::Joystick::Axis::PovY))
			ss << "pY";

		getLogger().info("Found controller, Name: " + id.name +
					 ", VendorID: " + std::to_string(id.vendorId) +
					 ", ProductID: " + std::to_string(id.productId) +
					 ", ButtonCount: " + std::to_string(buttonCount) +
					 ", Axis: " + ss.str());
	}
	getLogger().info("Found " + std::to_string(i) + " controllers");
}

void TitleScreen::hide() {
	getGame().removeWindowListener(this);
}

const std::string& TitleScreen::getName() const {
	return name;
}

void TitleScreen::windowClosed() {
	getGame().getWindow().close();
}
