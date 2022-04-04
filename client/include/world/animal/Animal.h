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

class AnimalState;

class Animal : public Renderable, public Physical, public Tickable, public Damager {
protected:
	mutable sf::Sprite sprite, debugSprite;
	b2Body* body;
	Forest& forest;

	std::vector<ForestNode*> path;
	int pathIndex = -1;
	b2Vec2 destination = b2Vec2(50.0f, 45.0f);
	float speed = 8.0f;
	bool facingRight = false, destinationChanged = false;

	std::shared_ptr<AnimalState> state;
public:
	Animal(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	Forest& getForest() override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	float getZOrder() const override;

	void tick(float delta) override;

	virtual b2Vec2 getDestination() const;

	virtual void setDestination(b2Vec2 destination);

	virtual std::shared_ptr<AnimalState> getState() const;

	virtual void setState(std::shared_ptr<AnimalState> state);

	void targetNearestEnemy();
};


#endif //LD50_CLIENT_ANIMAL_H
