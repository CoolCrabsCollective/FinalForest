//
// Created by cedric on 2022-04-02.
//

#include <world/Enemy.h>
#include "world/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"
#include "world/Forest.h"
#include "ForestScreen.h"

Tree::Tree(Forest& forest, b2Vec2 position) : forest(forest) {
	sprite.setTexture(*forest.getAssets().get(GameAssets::TREE));

    setDestroyedTexture(forest.getAssets().get(GameAssets::TREE_STUMP));
    setDamageStateSprite(&sprite);
    setHealth(10.0);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x / 4;

	fixture = body->CreateFixture(&circleShape, 0.0f);

	b2Filter filter;
	filter.categoryBits = 0x1000;
	filter.maskBits = 0xFFFF;

	fixture->SetFilterData(filter);
	timeLeftForNut = TIME_FOR_NUTSHOT;
}



void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(getForest().getScreen().getWindow());
    sf::Vector2f worldMousePos = getForest().getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	if((worldMousePos.x - sprite.getPosition().x)*(worldMousePos.x - sprite.getPosition().x) +
            (worldMousePos.y - sprite.getPosition().y)*(worldMousePos.y - sprite.getPosition().y) < 6)
    {
	    sprite.setColor(sf::Color(250, 253, 15, 127));
    }
	else
    {
        sprite.setColor(sf::Color(255, 255, 255, 255));
    }
	target.draw(sprite);
}



void Tree::tick(float delta) {

    if(timeLeftForNut >= 0)
    {
        timeLeftForNut -= delta / 1000.f;
    }
    else if(getSquirrelCount() > 0)
    {
        if(getForest().getEnemies().size() > 0)
        {
            Enemy* closestEnemy = getForest().getEnemies()[0];
            float closestDistance = b2DistanceSquared(getPosition(), closestEnemy->getPosition());
            for(int i = 1; i < getForest().getEnemies().size(); i++)
            {
                Enemy* enemy = getForest().getEnemies()[i];
                float dis = b2DistanceSquared(getPosition(), enemy->getPosition());
                if(dis < closestDistance)
                {
                    closestDistance = dis;
                    closestEnemy = enemy;
                }
            }

            getForest().shootNut(new NutShot(getForest(), {getPosition().x, getPosition().y}, closestEnemy));
            this->timeLeftForNut = TIME_FOR_NUTSHOT;
        }
    }
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
	return -getPosition().y + 100;
}

int Tree::getSquirrelCount() {
    return this->squirrels.size();
}

void Tree::addSquirrelTurret(Squirrel *squirrel) {
    squirrels.push_back(squirrel);
}

void Tree::damage(float attack) {
	bool wasDestroyed = isDestroyed();

	Damageable::damage(attack);

	if(isDestroyed() && !wasDestroyed) {
		squirrels.clear();
		b2Filter filter;
		filter.categoryBits = 0x1000;
		filter.maskBits = 0;

		fixture->SetFilterData(filter);
	}
}
