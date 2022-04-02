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
	sprite.setTexture(*forest.getAssets().get(GameAssets::GREAT_OAK));
}

void BigAssTree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

b2Vec2 BigAssTree::getSize() const {
	return {15.0f, 15.0f};
}
