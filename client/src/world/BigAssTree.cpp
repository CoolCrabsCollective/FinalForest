//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/BigAssTree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

BigAssTree::BigAssTree(Forest& forest, const b2Vec2& position)
	: Tree(forest, position)
{
	setHealth(100);
	sprite.setTexture(*forest.getAssets().get(GameAssets::GREAT_OAK), true);
}

b2Vec2 BigAssTree::getSize() const {
	return {15.0f, 15.0f};
}
