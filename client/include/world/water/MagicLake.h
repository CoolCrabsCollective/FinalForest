//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_MAGIC_LAKE_H
#define LD50_CLIENT_MAGIC_LAKE_H

#include "SFML/Graphics/Drawable.hpp"
#include "world/Obstacle.h"
#include "SFML/Graphics/Sprite.hpp"
#include "world/Renderable.h"


class MagicLake : public Renderable, public Obstacle {
	mutable sf::Sprite sprite;
	b2Body* body;
	Forest& forest;
public:
	MagicLake(Forest& forest, b2Vec2 position);

	Forest& getForest() override;

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	float getZOrder() const override;
};


#endif //LD50_CLIENT_MAGIC_LAKE_H
