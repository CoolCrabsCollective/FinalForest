//
// Created by Alexander Winter on 2022-04-02.
//

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
	debugSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

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

	if(!getForest().getScreen().isDebug())
		return;

	b2Vec2 prev = getPosition();
	if(!path.empty()) {
		for(ForestNode* node : path) {
			b2Vec2 nodeDest = node->getWorldPosition();
			b2Vec2 center = prev;
			center += nodeDest;
			center *= 0.5f;
			b2Vec2 size = nodeDest;
			size -= prev;

			float width = b2Distance(nodeDest, prev);

			sf::Vector2f vec = sf::Vector2f(nodeDest.x - prev.x, nodeDest.y - prev.y);
			vec.y *= -1.0f;

			debugSprite.setPosition(sf::Vector2f(center.x, 100.0f - center.y));
			debugSprite.setOrigin({ 0.5f, 0.5f });
			debugSprite.setScale(sf::Vector2f(width, 1.0f));
			debugSprite.setRotation(vec.angle());
			debugSprite.setColor(sf::Color::Red);

			target.draw(debugSprite);
			prev = nodeDest;
		}
	}
}

void Squirrel::tick(float delta) {
	sf::View view = sf::View({50.0f, 50.0f}, {213.33f, 120.0f});

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		const sf::RenderWindow& window = getForest().getScreen().getWindow();
		sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

		setDestination({pos.x, 100.0f - pos.y});
	}

	if(sf::Touch::isDown(1)) {
		const sf::RenderWindow& window = getForest().getScreen().getWindow();
		sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

		setDestination({pos.x, 100.0f - pos.y});
	}

	if(b2DistanceSquared(destination, getPosition()) < 1.f)
		return;

	if(destinationChanged) {
		if(!getForest().getPathFinder().findPath(getPosition(), destination, path))
			path.clear();
		destinationChanged = false;
	}

	b2Vec2 direction;

	if(path.empty())
		direction = destination - getPosition();
	else
		direction = path[path.size() - 1]->getWorldPosition() - getPosition();

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

const b2Vec2& Squirrel::getDestination() const {
	return destination;
}

void Squirrel::setDestination(const b2Vec2& destination) {
	Squirrel::destination = destination;
	destinationChanged = true;
}
