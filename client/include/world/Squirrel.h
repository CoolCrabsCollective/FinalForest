//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_SQUIRREL_H
#define LD50_CLIENT_SQUIRREL_H


#include "SFML/Graphics/Drawable.hpp"
#include "Physical.h"
#include "Tickable.h"

class Squirrel : public sf::Drawable, public Physical, public Tickable {
public:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	void tick(float delta) override;
};


#endif //LD50_CLIENT_SQUIRREL_H
