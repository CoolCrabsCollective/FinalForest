//
// Created by Alexander Winter on 2022-04-01.
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

class ForestScreen : public wiz::Screen, public wiz::WindowListener, public wiz::InputListener {
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


	sf::Text fpsText;
	sf::Text mouseCoordText;

	Forest forest;
    Menu* animalMenu;
    Menu* turretMenu;
    Tree* selectedTree;
public:
    Tree *getSelectedTree() const;

    void setSelectedTree(Tree *selectedTree);

private:

    bool debug = false;
	float fps = 0.0f;
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

	bool isDebug() const;

	void setDebug(bool debug);

    void keyPressed(const sf::Event::KeyEvent& keyEvent) override;

	void mouseButtonReleased(const sf::Event::MouseButtonEvent &mouseButtonEvent) override;

    void touchBegan(const sf::Event::TouchEvent& touchEvent) override;

    void setMenu(MenuType menuType);
};


#endif //WIZENGINEQUICKSTART_CLIENT_TOPDOWNSCREEN_H
