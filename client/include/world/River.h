//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_RIVER_H
#define LD50_CLIENT_RIVER_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Obstacle.h"
#include "Tickable.h"

class River : public sf::Drawable, public Obstacle, public Tickable {
	mutable sf::Sprite river_line, river_joint;
	b2Body* body;
	Forest& forest;
	std::vector<b2Vec2> path;
	float width;

	mutable float textureOffset = 0.0f;
public:
	River(Forest& forest, std::vector<b2Vec2> path, float width);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void tick(float delta) override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	Forest& getForest() const override;

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;
};


#endif //LD50_CLIENT_RIVER_H
