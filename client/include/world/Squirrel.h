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

class Squirrel : public sf::Drawable, public Physical, public Tickable {

	mutable sf::Sprite sprite;
	b2Body* body;
	Forest& forest;

	b2Vec2 destination = b2Vec2(100.f, 100.f);
	float speed = 10.0f;
	bool facingRight = false;
public:

	Forest& getForest() const override;

	Squirrel(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	void tick(float delta) override;
};


#endif //LD50_CLIENT_SQUIRREL_H
