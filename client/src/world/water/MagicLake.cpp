//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/water/MagicLake.h"
#include "world/Forest.h"
#include "Box2D/Box2D.h"
#include "GameAssets.h"

MagicLake::MagicLake(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::MAGIC_LAKE));
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(getSize().x / 2.0f, getSize().y / 4.0f);

	b2Fixture* fixture = body->CreateFixture(&polygonShape, 0.0f);

	b2Filter filter;
	filter.categoryBits = 0x1000;
	filter.maskBits = 0xFFFF;

	fixture->SetFilterData(filter);
}

Forest& MagicLake::getForest() {
	return forest;
}

bool MagicLake::isBlocking(b2Vec2 center, b2Vec2 size) {
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

b2Body* MagicLake::getBody() const {
	return body;
}

b2Vec2 MagicLake::getPosition() const {
	return body->GetPosition();
}

b2Vec2 MagicLake::getSize() const {
	return b2Vec2(20.0f, 20.0f);
}

void MagicLake::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

float MagicLake::getZOrder() const {
	return 1;
}
