//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_SQUIRREL_H
#define LD50_CLIENT_SQUIRREL_H


#include "world/animal/state/AnimalState.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "world/pathfinding/ForestNode.h"
#include "memory.h"
#include "Animal.h"
#include "world/enemy/Enemy.h"

class AnimalState;

class Squirrel : public Animal {
	sf::Texture* squirrelWalk;
	sf::Texture* squirrelIdle;
	sf::Texture* squirrelNut;
    sf::Texture* squirrelAttack;
public:
	Squirrel(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

protected:
	void noEnemyLeft() override;
};


#endif //LD50_CLIENT_SQUIRREL_H
