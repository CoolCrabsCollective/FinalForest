//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/BigAssTree.h"
#include "GameAssets.h"

BigAssTree::BigAssTree(Forest& forest, const b2Vec2& position)
	: Tree(forest, position)
{
	setHealth(100);
    setDestroyedTexture(forest.getAssets().get(GameAssets::GREAT_OAK_STUMP));
    setDamageStateSprite(&sprite);
	sprite.setTexture(*forest.getAssets().get(GameAssets::GREAT_OAK), true);
}

b2Vec2 BigAssTree::getSize() const {
	return {15.0f, 15.0f};
}

void BigAssTree::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    Tree::draw(target, states);
}

float BigAssTree::getZOrder() const {
    return -getPosition().y + 100 - .5f;
}
