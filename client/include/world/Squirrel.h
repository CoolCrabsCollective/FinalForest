//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_SQUIRREL_H
#define LD50_CLIENT_SQUIRREL_H


#include "SFML/Graphics/Drawable.hpp"
#include "Physical.h"
#include "Tickable.h"
#include "SFML/Graphics/Sprite.hpp"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "world/pathfinding/ForestNode.h"

class Squirrel : public sf::Drawable, public Physical, public Tickable {

	mutable sf::Sprite sprite, debugSprite;
	b2Body* body;
	Forest& forest;

	std::vector<ForestNode*> path;
	b2Vec2 destination = b2Vec2(75.f, 75.f);
	float speed = 10.0f;
	bool facingRight = false, destinationChanged = false;
public:

	Forest& getForest() const override;

	Squirrel(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	void tick(float delta) override;

	const b2Vec2& getDestination() const;

	void setDestination(const b2Vec2& destination);
};


#endif //LD50_CLIENT_SQUIRREL_H
