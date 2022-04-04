//
// Created by Alexander Winter on 2022-04-04.
//

#ifndef LD50_CLIENT_BULLDOZER_H
#define LD50_CLIENT_BULLDOZER_H


#include "Enemy.h"
#include "SFML/Graphics/RenderTarget.hpp"

class Bulldozer : public Enemy {
public:
	Bulldozer(Forest& forest, const b2Vec2& position);

	b2Vec2 getSize() const override;

	void tick(float delta) override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD50_CLIENT_BULLDOZER_H
