//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#include "world/animal/Bear.h"
#include "world/Forest.h"
#include "GameAssets.h"


Bear::Bear(Forest& forest, b2Vec2 position)
		: Animal(forest, position)
{
	sprite.setTexture(*forest.getAssets().get(GameAssets::BEAR));
}

b2Vec2 Bear::getSize() const {
	return b2Vec2(3.0f, 3.0f);
}
