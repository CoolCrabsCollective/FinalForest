//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIMAL_H
#define LD50_CLIENT_ANIMAL_H

#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damager.h"
#include "world/Renderable.h"
#include "world/pathfinding/ForestNode.h"

class Animal : public Renderable, public Physical, public Tickable, public Damager {
protected:
	mutable sf::Sprite sprite, debugSprite;
	b2Body* body;
	Forest& forest;

	std::vector<ForestNode*> path;
	int pathIndex = -1;
	b2Vec2 destination = b2Vec2(75.0f, 75.0f);
	float speed = 8.0f;
	bool facingRight = false, destinationChanged = false;
public:
	Animal(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	Forest& getForest() override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	float getZOrder() const override;

	void tick(float delta) override;

	virtual const b2Vec2& getDestination() const;

	virtual void setDestination(const b2Vec2& destination);
};


#endif //LD50_CLIENT_ANIMAL_H
