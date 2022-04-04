//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/animal/Animal.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "ForestScreen.h"
#include "Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "world/Physical.h"
#include "world/animal/state/AnimalGoAttackState.h"


Animal::Animal(Forest& forest, b2Vec2 position)
		: forest(forest)
{
	debugSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = this->getSize().x / 2.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);

	b2Filter filter;
	filter.categoryBits = 0x0001;
	filter.maskBits = 0x1000;

	fixture->SetFilterData(filter);
}

Forest& Animal::getForest() {
	return forest;
}

b2Body* Animal::getBody() const {
	return body;
}

b2Vec2 Animal::getPosition() const {
	return body->GetPosition();
}

float Animal::getZOrder() const {
	return -getPosition().y + 100;
}

void Animal::tick(float delta) {

	if(b2DistanceSquared(destination, getPosition()) < 1.f)
	{
		body->SetLinearVelocity({0.f, 0.f});
		return;
	}

	if(destinationChanged) {
		if(!getForest().getPathFinder().findPath(ANIMAL_UNIT, getPosition(), destination, path))
			path.clear();
		else
			pathIndex = 1;
		destinationChanged = false;
	}

	b2Vec2 direction;

	if(path.size() < 2 || pathIndex == -1)
		direction = destination - getPosition();
	else {
		direction = path[pathIndex]->getWorldPosition() - getPosition();

		if(direction.LengthSquared() < 1.0f) {
			pathIndex++;
			if(pathIndex == path.size())
			{
				pathIndex = -1;
				direction = destination - getPosition();
			}
			else
				direction = path[pathIndex]->getWorldPosition() - getPosition();
		}
	}

	facingRight = direction.x > 0;

	float speed = this->speed;

	if(direction.LengthSquared() > 1.0f)
		direction.Normalize();

	body->SetLinearVelocity(speed * direction);
}

void Animal::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

	float flip = facingRight > 0 ? -1.0f : 1.0f;

	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});
	target.draw(sprite);

	if(!forest.getScreen().isDebug())
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

			if(prev == getPosition()) {
				prev = nodeDest;
				continue;
			}

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


	debugSprite.setPosition(sf::Vector2f(destination.x, 100.0f - destination.y));
	debugSprite.setOrigin({ 0.5f, 0.5f });
	debugSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	debugSprite.setColor(sf::Color::Blue);

	target.draw(debugSprite);
}

b2Vec2 Animal::getDestination() const {
	return destination;
}

void Animal::setDestination(b2Vec2 destination) {
	Animal::destination = destination;
	destinationChanged = true;
}

b2Vec2 Animal::getSize() const {
	return b2Vec2(2.0f, 2.0f);
}

std::shared_ptr<AnimalState> Animal::getState() const {
	return state;
}

void Animal::setState(std::shared_ptr<AnimalState> state) {
	this->state = state;
}

void Animal::targetNearestEnemy() {
	if (forest.getEnemies().size() <= 1)
		return;

	std::vector enemies(forest.getEnemies());

	if (enemies.size() > 2) {
		std::sort(enemies.begin(), enemies.end() - 1, [this](Enemy* a, Enemy* b){
			float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
			float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
			return a_dis < b_dis;
		});
	}

	for (Enemy* enemy : enemies) {
		if (!enemy->isDestroyed()) {
			this->state = std::make_shared<AnimalGoAttackState>(this, enemy);
			break;
		}
	}
}