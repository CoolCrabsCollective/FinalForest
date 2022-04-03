//
// Created by William Wells on 2022-04-02.
//

#include <world/state/LumberJackIdleState.h>
#include <world/state/LumberJackGoAttackState.h>

#include "world/LumberJack.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "ForestScreen.h"

LumberJack::LumberJack(Forest& forest, b2Vec2 position) : forest(forest) {
    sprite.setTexture(*forest.getAssets().get(GameAssets::LUMBERJACKAXE));
	debugSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

    // Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

    this->state = std::make_shared<LumberJackIdleState>(&this->forest, this);

    targetNearestTree();
}

void LumberJack::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({getPosition().x, 100.0f - getPosition().y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

	float flip = facingRight > 0 ? 1.0f : -1.0f;

	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});
	target.draw(sprite);


	if(!getForest().getScreen().isDebug())
		return;

	b2Vec2 prev = getPosition();
	if(path.size() >= 2 && pathIndex != -1) {
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
			debugSprite.setColor(sf::Color::Black);

			target.draw(debugSprite);
			prev = nodeDest;
		}
	}


	debugSprite.setPosition(sf::Vector2f(destination.x, 100.0f - destination.y));
	debugSprite.setOrigin({ 0.5f, 0.5f });
	debugSprite.setScale(sf::Vector2f(1.0f, 1.0f));
	debugSprite.setColor(sf::Color::Cyan);

	target.draw(debugSprite);
}

void LumberJack::tick(float delta) {
    if (target->isDestroyed()) {
        this->state = std::make_shared<LumberJackIdleState>(&this->forest, this);
        targetNearestTree();
    }

    this->state->tick(delta);

	if(b2DistanceSquared(destination, getPosition()) < 1.f)
	{
		body->SetLinearVelocity({0.f, 0.f});
		return;
	}

	if(destinationChanged) {
		if(!getForest().getPathFinder().findPath(getPosition(), destination, path))
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

b2Body* LumberJack::getBody() const {
	return body;
}

b2Vec2 LumberJack::getPosition() const {
	return body->GetPosition();
}

b2Vec2 LumberJack::getSize() const {
	return b2Vec2(1.5f, 1.5f);
}

b2Vec2 LumberJack::getDestination() const {
    return destination;
}

Forest& LumberJack::getForest() const {
	return forest;
}

float LumberJack::getSpeed() const {
    return speed;
}

Tree* LumberJack::getTarget() const {
    return target;
}

float LumberJack::getAttack() const {
    return attack;
}

void LumberJack::setSpeed(float speed) {
    this->speed = speed;
}

void LumberJack::setAttack(float attack) {
    this->attack = attack;
}

void LumberJack::setFacingRight(bool facingRight) {
    this->facingRight = facingRight;
}

void LumberJack::targetNearestTree() {
    if (forest.getAliveTrees().size() <= 0) {
        return;
    }

    std::vector<Tree*> trees(forest.getAliveTrees());

    if (trees.size() > 2) {
        std::sort(trees.begin(), trees.end(), [this](Tree* a, Tree* b){
            float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
            float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
            return a_dis < b_dis;
        });
    }

    target = trees.front();
	setDestination(target->getPosition());

    this->state = std::make_shared<LumberJackGoAttackState>(&this->forest, this);
}

std::shared_ptr<LumberJackState> LumberJack::getState() const {
    return state;
}

void LumberJack::setState(std::shared_ptr<LumberJackState> state) {
    LumberJack::state = state;
}

void LumberJack::setDestination(b2Vec2 destination) {
	LumberJack::destination = destination;
	destinationChanged = true;
}

float LumberJack::getZOrder() const {
	return getPosition().y + 100;
}
