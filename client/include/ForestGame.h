//
// Created by Winter on 12/02/2022.
//

#ifndef GAMETEMPLATE_EXAMPLEGAME_H
#define GAMETEMPLATE_EXAMPLEGAME_H

#include <WIZ/game/BasicGame.h>

class ForestGame : public wiz::BasicGame {
public:
	ForestGame(std::shared_ptr<sf::RenderWindow> window,
			   std::shared_ptr<wiz::Logger> logger,
			   std::shared_ptr<wiz::AssetLoader> assetLoader);
};


#endif //GAMETEMPLATE_EXAMPLEGAME_H
