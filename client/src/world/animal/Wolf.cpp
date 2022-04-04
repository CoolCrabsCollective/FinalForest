//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#include "world/animal/Wolf.h"
#include "world/Forest.h"
#include "GameAssets.h"


Wolf::Wolf(Forest& forest, b2Vec2 position)
	: Animal(forest, position)
{
	sprite.setTexture(*forest.getAssets().get(GameAssets::WOLF));
}

b2Vec2 Wolf::getSize() const {
	return b2Vec2(2.0f, 2.0f);
}
