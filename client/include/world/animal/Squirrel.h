//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_SQUIRREL_H
#define LD50_CLIENT_SQUIRREL_H


#include "world/state/SquirrelState.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "world/pathfinding/ForestNode.h"
#include "memory.h"
#include "Animal.h"

class SquirrelState;

class Squirrel : public Animal {
	sf::Texture* squirrelWalk;
	sf::Texture* squirrelIdle;
	sf::Texture* squirrelNut;

	std::shared_ptr<SquirrelState> state;
public:
	Squirrel(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

    void tick(float delta) override;

	std::shared_ptr<SquirrelState> getState() const;

	void setState(std::shared_ptr<SquirrelState> state);

    void targetNearestEnemy();
};


#endif //LD50_CLIENT_SQUIRREL_H
