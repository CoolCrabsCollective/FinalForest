//
// Created by Alexander Winter on 2022-04-02.
//

#include <world/state/SquirrelIdleState.h>

#include <memory>
#include <world/state/SquirrelGatherState.h>
#include <world/state/SquirrelReturnGatherState.h>
#include <world/state/SquirrelGoGathertState.h>
#include <world/state/SquirrelGoAttackState.h>
#include "world/Squirrel.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Window/Mouse.hpp"
#include "ForestScreen.h"

Squirrel::Squirrel(Forest& forest, b2Vec2 position) : forest(forest) {
    setPower(1.0);

    squirrelWalk = forest.getAssets().get(GameAssets::SQUIRREL);
    squirrelIdle = forest.getAssets().get(GameAssets::SQUIRREL_IDLE);
    squirrelNut = forest.getAssets().get(GameAssets::SQUIRREL_WITH_NUT);
	sprite.setTexture(*squirrelWalk);
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
	b2Fixture* fixture = body->CreateFixture(&fixtureDef);

	b2Filter filter;
	filter.categoryBits = 0x0001;
	filter.maskBits = 0x1000;

	fixture->SetFilterData(filter);

	this->state = std::make_shared<SquirrelIdleState>(&this->forest, this);
    // Update the squirrel count.
    forest.squirrelCount++;
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

void Squirrel::tick(float delta) {

    if(dynamic_pointer_cast<SquirrelIdleState>(state).get() || dynamic_pointer_cast<SquirrelGatherState>(state).get())
    {
        sprite.setTexture(*squirrelIdle);
    }
    else if(dynamic_pointer_cast<SquirrelReturnGatherState>(state).get())
    {
        sprite.setTexture(*squirrelNut);
    }
    else
    {
        sprite.setTexture(*squirrelWalk);
    }

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
	destinationChanged = true;
}

std::shared_ptr<SquirrelState> Squirrel::getState() const {
    return state;
}

void Squirrel::setState(std::shared_ptr<SquirrelState> state) {
    Squirrel::state = state;
}

void Squirrel::targetNearestEnemy() {
    if (forest.getEnemies().size() <= 0) {
        return;
    }

    std::vector enemies(forest.getEnemies());

    if (enemies.size() > 2) {
        std::sort(enemies.begin(), enemies.end(), [this](Enemy* a, Enemy* b){
            float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
            float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
            return a_dis < b_dis;
        });
    }

    this->state = std::make_shared<SquirrelGoAttackState>(&this->forest, this, enemies.front());
}

float Squirrel::getZOrder() const {
	return -getPosition().y + 100;
}
