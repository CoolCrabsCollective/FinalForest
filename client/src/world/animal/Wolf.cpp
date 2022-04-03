//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/animal/Wolf.h"


Wolf::Wolf(Forest& forest, b2Vec2 position)
	: forest(forest)
{

}

Forest& Wolf::getForest() const {
	return forest;
}

b2Body* Wolf::getBody() const {
	return nullptr;
}

b2Vec2 Wolf::getPosition() const {
	return b2Vec2();
}

b2Vec2 Wolf::getSize() const {
	return b2Vec2();
}

float Wolf::getZOrder() const {
	return 0;
}

void Wolf::tick(float delta) {

}
