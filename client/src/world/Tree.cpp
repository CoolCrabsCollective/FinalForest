//
// Created by cedric on 2022-04-02.
//

#include "world/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"
#include "world/Forest.h"


Tree::Tree(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	b2Body* body = forest.getB2World().CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
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
	return b2Vec2(1.0f, 1.0f);
}

Forest& Tree::getForest() const {
	return forest;
}
