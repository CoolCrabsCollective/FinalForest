//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/AssTree.h"
#include "GameAssets.h"

AssTree::AssTree(Forest& forest, const b2Vec2& position)
	: Tree(forest, position)
{
	setHealth(100);
	sprite.setTexture(*forest.getAssets().get(GameAssets::GREAT_OAK), true);
}

b2Vec2 AssTree::getSize() const {
	return {15.0f, 15.0f};
}
