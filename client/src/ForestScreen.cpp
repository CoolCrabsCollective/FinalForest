//
// Created by Alexander Winter🤤 on 2022-04-01.
//

#include <UI/AnimalMenu.h>
#include <UI/TurretMenu.h>
#include <UI/EnemyMenu.h>
#include <iostream>
#include <memory>
#include "ForestScreen.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "GameAssets.h"
#include "UI/Button.h"
#include "world/tree/BigAssTree.h"
#include "WIZ/game/BasicGame.h"
#include "TitleScreen.h"

ForestScreen::ForestScreen(wiz::Game& game)
		: Screen(game),
        forest(*this, game.getAssets()),
        animalMenu(new AnimalMenu(game.getAssets(), forest)),
        turretMenu(new TurretMenu(game.getAssets(), forest)),
        enemyMenu(new EnemyMenu(game.getAssets(), forest)),
        wavePopUp(game.getAssets()) {

    animalMenu->show(true);
    turretMenu->show(false);
    enemyMenu->show(false);

	music = getGame().getAssets().get(GameAssets::NUTLIFE);
	music->setVolume(50.0f);
	music->setLoop(true);

	gameoverSound.setBuffer(*getGame().getAssets().get(GameAssets::GAMEOVER));
	gameoverSound.setVolume(100.0f);
	waveStartSound.setBuffer(*getGame().getAssets().get(GameAssets::WAVE_START));
	waveStartSound.setVolume(100.0f);
	waveClearedSound.setBuffer(*getGame().getAssets().get(GameAssets::WAVE_CLEARED));
	waveClearedSound.setVolume(100.0f);
}

void ForestScreen::tick(float delta) {
    if (gameOver)
        return;

	forest.tick(delta);
	animalMenu->tick(delta);
	turretMenu->tick(delta);
    enemyMenu->tick(delta);
    wavePopUp.tick(delta);
    updateSquirrelCount();
    updateNutCount();
    updateMana();
    updateWave();
	fps = 1.0f / delta * 1000.0f;

    // Next wave detection
    if (forest.enemies.empty()) {
        forest.waveState.difficulty += 0.5;
        forest.waveState.round++;
        forest.generateEnemyWave();
        wavePopUp.popUp("Wave " + std::to_string(forest.waveState.round), 1000);
    }

    // Game over detection.
    if (forest.getGreatOakTree()->isDestroyed()) {
        gameOverText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));
        gameOverText.setCharacterSize(50);
        gameOverText.setString("          Game Over!\nYou survived " + std::to_string(forest.waveState.round - 1) + " waves!");
        sf::FloatRect bounds = gameOverText.getLocalBounds();
        gameOverText.setPosition(sf::Vector2f(800 - bounds.getSize().x / 2, 450 - bounds.getSize().y / 2));

        resetButton = new WordsButton(
            sf::IntRect({800 - 100, 450 - 25 + 150}, {200, 50}),
            forest,
            [&](Button* button) {
				getGame().setScreen(std::make_shared<TitleScreen>(getGame()));
            },
            "Restart"
            );

        gameOver = true;
		music->stop();
		gameoverSound.play();
    }
}

void ForestScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.setView(sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));
    target.draw(forest);
    target.setView(sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));
    target.draw(nutCountText);
    target.draw(nutSprite);
    target.draw(squirrelCountText);
    target.draw(squirrelSprite);
    target.draw(manaText);
    target.draw(manaSprite);
    target.draw(waveText);
    target.draw(*animalMenu);
    target.draw(*turretMenu);
    target.draw(*enemyMenu);
    target.draw(wavePopUp);

    if (gameOver) {
        target.draw(gameOverText);
        target.draw(*resetButton);
    }

	if(debug) {
		fpsText.setString("FPS: " + std::to_string(fps));
		target.draw(fpsText);

		sf::Vector2f pos = getWindow().mapPixelToCoords(sf::Mouse::getPosition(getWindow()), sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));
		pos.y = 100.0f - pos.y;
		mouseCoordText.setString("Mouse pos: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
		target.draw(mouseCoordText);
	}
}

void ForestScreen::show() {
    nutTexture = getGame().getAssets().get(GameAssets::NUT);
    nutSprite.setTexture(*nutTexture);
    nutSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    nutSprite.setColor(sf::Color(255, 255, 255, 200));
    nutSprite.setPosition(sf::Vector2f(1500.0f, 25.0f));
    nutSprite.setScale({2.0f, 2.0f});

    squirrelTexture = getGame().getAssets().get(GameAssets::SQUIRREL);
    squirrelSprite.setTexture(*squirrelTexture);
    squirrelSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    squirrelSprite.setColor(sf::Color(255, 255, 255, 200));
    squirrelSprite.setPosition(sf::Vector2f(1500.0f, 75.0f));
    squirrelSprite.setScale({2.0f, 2.0f});

    manaTexture = getGame().getAssets().get(GameAssets::MANA);
    manaSprite.setTexture(*manaTexture);
    manaSprite.setTextureRect(sf::Rect<int>({0, 0}, {16, 16}));
    manaSprite.setColor(sf::Color(255, 255, 255, 200));
    manaSprite.setPosition(sf::Vector2f(1500.0f, 125.0f));
    manaSprite.setScale({2.0f, 2.0f});

	fpsText.setString("FPS: ");
	fpsText.setPosition(sf::Vector2f(50, 875));
	fpsText.setCharacterSize(20);
	fpsText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

	mouseCoordText.setString("Mouse pos: ");
	mouseCoordText.setPosition(sf::Vector2f(50, 850));
	mouseCoordText.setCharacterSize(20);
	mouseCoordText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

    squirrelCountText.setPosition(sf::Vector2f(1550, 25));
    squirrelCountText.setCharacterSize(20);
    squirrelCountText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

    nutCountText.setPosition(sf::Vector2f(1550, 75));
    nutCountText.setCharacterSize(20);
    nutCountText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

    manaText.setPosition(sf::Vector2f(1550, 125));
    manaText.setCharacterSize(20);
    manaText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

    waveText.setPosition(sf::Vector2f(1500, 175));
    waveText.setCharacterSize(20);
    waveText.setFont(*getGame().getAssets().get(GameAssets::DEFAULT_FONT));

	getGame().addWindowListener(this);
	getGame().addInputListener(this);

	music->play();

    wavePopUp.popUp("Wave " + std::to_string(forest.waveState.round), 1000);
}

void ForestScreen::hide() {
	getGame().removeWindowListener(this);
	getGame().removeInputListener(this);
}

const std::string& ForestScreen::getName() const {
	return name;
}

void ForestScreen::windowClosed() {
	getGame().getWindow().close();
}

void ForestScreen::updateNutCount() {
    squirrelCountText.setString(std::to_string(forest.nutCount));
}

void ForestScreen::updateSquirrelCount() {
    nutCountText.setString(std::to_string(forest.squirrelCount));
}

void ForestScreen::updateMana() {
    manaText.setString(std::to_string(forest.mana));
}

void ForestScreen::updateWave() {
    waveText.setString("Wave: " + std::to_string(forest.waveState.round));
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
	if(keyEvent.code == sf::Keyboard::F7)
		forest.nutCount += 100;
}

void ForestScreen::mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) {
	sf::Vector2f clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y), UI_VIEW);

	if(gameOver) {
		resetButton->checkClick(clickVector);
		return;
	}
    clickActiveMenu(clickVector);

    clickVector = getWindow().mapPixelToCoords(sf::Vector2i(mouseButtonEvent.x, mouseButtonEvent.y), GAME_VIEW);
    entityClickSelection.clickScan(clickVector, forest);
}

void ForestScreen::touchBegan(const sf::Event::TouchEvent &touchScreenEvent) {
    sf::Vector2f touchVector = getWindow().mapPixelToCoords(sf::Vector2i(touchScreenEvent.x, touchScreenEvent.y), UI_VIEW);

	if(gameOver) {
		resetButton->checkClick(touchVector);
		return;
	}

	clickActiveMenu(touchVector);
    touchVector = getWindow().mapPixelToCoords(sf::Vector2i(touchScreenEvent.x, touchScreenEvent.y), GAME_VIEW);
    entityClickSelection.clickScan(touchVector, forest);
}

void ForestScreen::clickActiveMenu(sf::Vector2f clickVector) {
    switch (activeMenu) {
        case ANIMAL_MENU:
            animalMenu->click(clickVector);
            break;
        case TURRET_MENU:
            turretMenu->click(clickVector);
            break;
        case ENEMY_MENU:
            enemyMenu->click(clickVector);
            break;
    }
}

void ForestScreen::setMenu(MenuType menuType) {
    activeMenu = menuType;
    switch (menuType) {
        case ANIMAL_MENU:
            animalMenu->show(true);
            turretMenu->show(false);
            enemyMenu->show(false);
            break;
        case TURRET_MENU:
            animalMenu->show(false);
            turretMenu->show(true);
            enemyMenu->show(false);
            break;
        case ENEMY_MENU:
            animalMenu->show(false);
            turretMenu->show(false);
            enemyMenu->show(true);
            break;
    }
}

EntityClickSelection &ForestScreen::getEntityClickSelection() {
    return entityClickSelection;
}

void ForestScreen::setEntityClickSelection(const EntityClickSelection &entityClickSelection) {
    ForestScreen::entityClickSelection = entityClickSelection;
}
