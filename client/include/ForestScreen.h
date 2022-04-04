//
// Created by Alexander Winter🤤 on 2022-04-01.
//

#ifndef WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H
#define WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H

#include <UI/MenuType.h>
#include "WIZ/game/Screen.h"
#include "WIZ/game/WindowListener.h"
#include "Box2D/Dynamics/b2World.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "world/Forest.h"
#include "SFML/Graphics/Texture.hpp"
#include "../cmake-build-debug/_deps/sfml-src/include/SFML/Window/Event.hpp"
#include "UI/Menu.h"
#include "SFML/Audio/Music.hpp"
#include "UI/WordsButton.h"
#include "UI/EntityClickSelection.h"
#include "UI/PopUp.h"
#include "SFML/Audio/Sound.hpp"

class ForestScreen : public wiz::Screen, public wiz::WindowListener, public wiz::InputListener {
	const sf::View UI_VIEW = sf::View({800.0f, 450.0f}, {1600.0f, 900.0f});
	const sf::View GAME_VIEW = sf::View({50.0f, 50.0f}, {195.56f, 110.0f});

	std::string name = "ForestScreen";

    sf::Text nutCountText;
    sf::Texture* nutTexture;
    sf::Sprite nutSprite;
    sf::Text squirrelCountText;
    sf::Texture* squirrelTexture;
    sf::Sprite squirrelSprite;
    sf::Text manaText;
    sf::Texture* manaTexture;
    sf::Sprite manaSprite;
    sf::Text waveText;

    PopUp wavePopUp;

	sf::Text fpsText;
	sf::Text mouseCoordText;

    sf::Text gameOverText, pausedText;
    WordsButton* resetButton;

	sf::Music* music;
	sf::Sound gameoverSound, waveStartSound, waveClearedSound;
	sf::Sound click;

	Forest forest;
    Menu* animalMenu;
    Menu* turretMenu;
    Menu* enemyMenu;
    MenuType activeMenu = ANIMAL_MENU;

    EntityClickSelection entityClickSelection;

    bool debug = false;
	float fps = 0.0f;
    bool gameOver = false, paused = false;
    bool waitingForNextWave = false;
    float timeTillNextWave = 0.0f;

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

    void updateWave();

	bool isDebug() const;

	void setDebug(bool debug);

    void keyPressed(const sf::Event::KeyEvent& keyEvent) override;

	void mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) override;

    void touchBegan(const sf::Event::TouchEvent& touchEvent) override;

    void clickActiveMenu(sf::Vector2f clickVector);

    void setMenu(MenuType menuType);

    EntityClickSelection& getEntityClickSelection();

    void setEntityClickSelection(const EntityClickSelection &entityClickSelection);

	sf::Sound& getClick();
};


#endif //WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H
