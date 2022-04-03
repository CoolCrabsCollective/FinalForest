//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_RIVER_H
#define LD50_CLIENT_RIVER_H

#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "world/Obstacle.h"
#include "world/Tickable.h"
#include "world/Renderable.h"
#include "Bridge.h"

class River : public Renderable, public Obstacle, public Tickable {
	mutable sf::Sprite river_line, river_joint;
	b2Body* body;
	Forest& forest;
	std::vector<b2Vec2> path;
	std::vector<b2Fixture*> fixtures;
	std::vector<Bridge*> bridges;
	float width;

	mutable float textureOffset = 0.0f;
public:
	River(Forest& forest, std::vector<b2Vec2> path, float width);

	~River();

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void tick(float delta) override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	Forest& getForest() override;

	const Forest& getForest() const;

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;

	float getZOrder() const override;

	const std::vector<b2Vec2>& getPath() const;

	const std::vector<Bridge*>& getBridges() const;

	void addBridge(Bridge* bridge);

	static bool isBlocking(std::vector<b2Vec2> path, float width, b2Vec2 center, b2Vec2 size);
};


#endif //LD50_CLIENT_RIVER_H
