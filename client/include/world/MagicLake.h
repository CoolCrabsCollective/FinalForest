//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_MAGICLAKE_H
#define LD50_CLIENT_MAGICLAKE_H

#include "SFML/Graphics/Drawable.hpp"
#include "Obstacle.h"
#include "SFML/Graphics/Sprite.hpp"


class MagicLake : public sf::Drawable, public Obstacle {
	mutable sf::Sprite sprite;
	b2Body* body;
	Forest& forest;
public:
	MagicLake(Forest& forest, b2Vec2 position);

	Forest& getForest() const override;

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD50_CLIENT_MAGICLAKE_H
