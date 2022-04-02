//
// Created by Alexander Winter on 2022-04-02.
//

#include <world/state/SquirrelIdleState.h>

#include <memory>
#include "world/Squirrel.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Mouse.hpp"
#include "SFML/Window/Touch.hpp"
#include "ForestScreen.h"

Squirrel::Squirrel(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::SQUIRREL));

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	this->state = std::make_shared<SquirrelIdleState>(&this->forest, this);
    // Update the squirrel count.
    forest.squirrelCount ++;
}

void Squirrel::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

	float flip = facingRight > 0 ? -1.0f : 1.0f;

	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});
	target.draw(sprite);
}

void Squirrel::tick(float delta) {
	if(b2DistanceSquared(destination, getPosition()) < 1.f)
		return;

	b2Vec2 direction = destination - getPosition();
	facingRight = direction.x > 0;
	direction.Normalize();
	body->SetLinearVelocity(speed * direction);
}

b2Body* Squirrel::getBody() const {
	return body;
}

b2Vec2 Squirrel::getPosition() const {
	return body->GetPosition();
}

b2Vec2 Squirrel::getSize() const {
	return b2Vec2(1.5f, 1.5f);
}

Forest& Squirrel::getForest() const {
	return forest;
}

const b2Vec2 &Squirrel::getDestination() const {
    return destination;
}

void Squirrel::setDestination(const b2Vec2 &destination) {
    Squirrel::destination = destination;
}

std::shared_ptr<SquirrelState> Squirrel::getState() const {
    return state;
}

void Squirrel::setState(std::shared_ptr<SquirrelState> state) {
    Squirrel::state = state;
}
