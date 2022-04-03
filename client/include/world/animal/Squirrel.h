//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_SQUIRREL_H
#define LD50_CLIENT_SQUIRREL_H


#include "world/state/SquirrelState.h"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "world/pathfinding/ForestNode.h"
#include "memory.h"
#include "world/enemy/Enemy.h"

class SquirrelState;

class Squirrel : public Renderable, public Physical, public Tickable, public Damager {

	mutable sf::Sprite sprite, debugSprite;
	b2Body* body;
	Forest& forest;
	sf::Texture* squirrelWalk;
	sf::Texture* squirrelIdle;
	sf::Texture* squirrelNut;
    sf::Texture* squirrelAttack;

	std::vector<ForestNode*> path;
	int pathIndex = -1;
	b2Vec2 destination = b2Vec2(75.f, 75.f);
	float speed = 8.0f;
	bool facingRight = false, destinationChanged = false;

	std::shared_ptr<SquirrelState> state;
public:
	Squirrel(Forest& forest, b2Vec2 position);

	Forest& getForest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

    void tick(float delta) override;

	const b2Vec2& getDestination() const;

	void setDestination(const b2Vec2& destination);

	std::shared_ptr<SquirrelState> getState() const;

	void setState(std::shared_ptr<SquirrelState> state);

    void targetNearestEnemy();

	float getZOrder() const override;
};


#endif //LD50_CLIENT_SQUIRREL_H
