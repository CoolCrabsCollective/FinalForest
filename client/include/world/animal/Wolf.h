//
// Created by Alexander Winter on 2022-04-03.
//

#ifndef LD50_CLIENT_WOLF_H
#define LD50_CLIENT_WOLF_H

#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damager.h"
#include "world/Renderable.h"

class Wolf : public Renderable, public Physical, public Tickable, public Damager {
	mutable sf::Sprite sprite;

	Forest& forest;

public:
	Wolf(Forest& forest, b2Vec2 position);

	Forest& getForest() const;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	float getZOrder() const override;

	void tick(float delta) override;
};


#endif //LD50_CLIENT_WOLF_H
