//
// Created by cedric on 2022-04-02.
//

#include "world/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"
#include "world/Forest.h"


Tree::Tree(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::TREE));

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x / 4;

	b2Fixture* fixture = body->CreateFixture(&circleShape, 0.0f);

	b2Filter filter;
	filter.categoryBits = 0x1000;
	filter.maskBits = 0xFFFF;

	fixture->SetFilterData(filter);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

b2Body* Tree::getBody() const {
	return body;
}

b2Vec2 Tree::getPosition() const {
	return body->GetPosition();
}

b2Vec2 Tree::getSize() const {
	return {5.0f, 5.0f};
}

Forest& Tree::getForest() const {
	return forest;
}

bool Tree::isDestroyed() const {
    return destroyed;
}

void Tree::setHealth(float health) {
	this->health = health;
}

void Tree::damage(float damage) {
    health -= damage;

    if (health <= 0) {
        sprite.setTexture(*forest.getAssets().get(GameAssets::TREE_STUMP));
        destroyed = true;
    }
}

bool Tree::isBlocking(b2Vec2 center, b2Vec2 size) {
	size *= 0.5f;
	if(body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), center))
		return true;

	b2Vec2 topRight = center + size;
	if(body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), topRight))
		return true;

	b2Vec2 topLeft = center;
	topLeft.x -= size.x;
	topLeft.y += size.y;
	if(body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), topLeft))
		return true;

	b2Vec2 bottomLeft = center - size;
	if(body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), bottomLeft))
		return true;

	b2Vec2 bottomRight = center;
	bottomRight.x += size.x;
	bottomRight.y -= size.y;
	if(body->GetFixtureList()->GetShape()->TestPoint(body->GetTransform(), bottomRight))
		return true;

	return false;
}

float Tree::getZOrder() const {
	return getPosition().y + 100;
}
