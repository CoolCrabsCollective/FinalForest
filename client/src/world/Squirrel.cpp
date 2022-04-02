//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Squirrel.h"

void Squirrel::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

}

b2Body* Squirrel::getBody() const {
	return nullptr;
}

b2Vec2 Squirrel::getPosition() const {
	return b2Vec2();
}

b2Vec2 Squirrel::getSize() const {
	return b2Vec2();
}

void Squirrel::tick(float delta) {

}
