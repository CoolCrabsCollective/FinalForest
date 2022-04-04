//
// Created by Sir Dick on 2022-04-02.
//

#include "world/enemy/Enemy.h"
#include "world/tree/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"
#include "world/Forest.h"
#include "ForestScreen.h"

Tree::Tree(Forest& forest, b2Vec2 position) : forest(forest), healthBar(this, this, forest.assetLoader) {
    // Normal tree and turrets textures needs to be pointers! Copying them will crash on the switch
    // This is an issue that is supposed to be fixed in switch-sfml
    normalTreeTexture = forest.getAssets().get(GameAssets::TREE);
    turretTreeTexture = forest.getAssets().get(GameAssets::TREE_TURRET);

	sprite.setTexture(*normalTreeTexture);
	whiteTreeSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_TREE));
    labelSquirrelCount.setFont(*forest.getAssets().get(GameAssets::DEFAULT_FONT));

    labelSquirrelCount.setCharacterSize(24);
    labelSquirrelCount.setFillColor(sf::Color::Black);

    setDestroyedTexture(forest.getAssets().get(GameAssets::TREE_STUMP));
    setDamageStateSprite(&sprite);
    maxHealth = 10.0f;
    setHealth(maxHealth);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = getSize().x / 4;

	fixture = body->CreateFixture(&circleShape, 0.0f);

	b2Filter filter;
	filter.categoryBits = 0x1000;
	filter.maskBits = 0;

	fixture->SetFilterData(filter);
	timeLeftForNut = TIME_FOR_NUTSHOT;
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
    sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
    sf::Vector2f worldMousePos = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

    if(getSquirrelCount() > 0) {
        sf::View windowView = sf::View(sf::Vector2f(forest.getScreen().getWindow().getSize().x / 2.f, forest.getScreen().getWindow().getSize().y / 2.f), sf::Vector2f (forest.getScreen().getWindow().getSize()));
        target.setView(windowView);
        target.draw(labelSquirrelCount);
        target.setView(sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));
    }

	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

	if(this->forest.getScreen().getEntityClickSelection().getSelectedEntity() == this)
    {
        whiteTreeSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
        whiteTreeSprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
        whiteTreeSprite.setScale({1.2f * getSize().x / sprite.getTexture()->getSize().x, 1.2f * getSize().y / sprite.getTexture()->getSize().y});

        target.draw(whiteTreeSprite);
    }

    sprite.setColor(sf::Color(255, 255, 255, 255));
    sprite.setScale({getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
	target.draw(sprite);

    target.draw(healthBar);
}

void Tree::tick(float delta) {
    sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
    sf::Vector2f worldMousePos = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

    labelSquirrelCount.setString(std::to_string(squirrels));

    sf::Vector2 v = forest.getScreen().getWindow().mapCoordsToPixel({this->getPosition().x + 2, 100.f - this->getPosition().y - 5}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

    labelSquirrelCount.setPosition({(float)v.x, (float)v.y});

    if(timeLeftForNut >= 0) {
        timeLeftForNut -= delta / 1000.f;
    } else if(getSquirrelCount() > 0) {
        if(getForest().getEnemies().size() > 0) {
            Enemy* closestEnemy = getForest().getEnemies()[0];
            float closestDistance = b2DistanceSquared(getPosition(), closestEnemy->getPosition());
            for(int i = 1; i < getForest().getEnemies().size(); i++) {
                Enemy* enemy = getForest().getEnemies()[i];
                if (!enemy->isDestroyed()) {
                    float dis = b2DistanceSquared(getPosition(), enemy->getPosition());
                    if (dis < closestDistance) {
                        closestDistance = dis;
                        closestEnemy = enemy;
                    }
                }
            }

            if(closestDistance < 30*30 && forest.nutCount > 0) {
                forest.nutCount--;
                getForest().shootNut(new NutShot(getForest(), {getPosition().x, getPosition().y}, closestEnemy));
                this->timeLeftForNut = TIME_FOR_NUTSHOT / this->getSquirrelCount();
            }
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

Forest& Tree::getForest() {
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

int Tree::getSquirrelCount() const {
    return squirrels;
}

void Tree::addSquirrelTurret() {
    if (squirrels == 0)
        sprite.setTexture(*turretTreeTexture);

    squirrels++;
}

void Tree::damage(float attack) {
	bool wasDestroyed = isDestroyed();

	Damageable::damage(attack);

	if(isDestroyed() && !wasDestroyed) {
		squirrels = 0;
		b2Filter filter;
		filter.categoryBits = 0x1000;
		filter.maskBits = 0;

		fixture->SetFilterData(filter);
	}
}

void Tree::removeSquirrelTurret() {
    if (squirrels == 0)
        sprite.setTexture(*normalTreeTexture);

    if(getSquirrelCount() > 0)
        squirrels--;
}

const sf::Sprite &Tree::getSprite() const {
    return sprite;
}
