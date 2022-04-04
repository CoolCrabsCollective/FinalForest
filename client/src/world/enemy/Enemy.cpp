//
// Created by Cedric on 2022-04-03.
//

#include "world/enemy/Enemy.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "world/enemy/state/EnemyIdleState.h"
#include "world/enemy/state/EnemyAttackState.h"
#include "world/enemy/state/EnemyLeaveState.h"
#include "ForestScreen.h"
#include "world/Forest.h"
#include "world/Damageable.h"
#include "world/Damager.h"
#include "world/animal/Animal.h"

Enemy::Enemy(Forest& forest, b2Vec2 position) : forest(forest), healthBar(this, this, forest.assetLoader) {
	setStateSprite(&sprite);

	setDamageStateSprite(&sprite);

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
	filter.categoryBits = 0x0002;
	filter.maskBits = 0x3002;

	fixture->SetFilterData(filter);

	this->state = std::make_shared<EnemyIdleState>(this);

	targetNearestTree();

	maxHealth = 3.0f;
	setHealth(maxHealth);
}

void Enemy::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	if(this->isDestroyed())
		return;

	sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
	sf::Vector2f worldMousePos = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});

	float flip = facingRight > 0 ? 1.0f : -1.0f;

	if(this->forest.getScreen().getEntityClickSelection().getSelectedEntity() == this)
	{
		whiteSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
		whiteSprite.setOrigin({0.5f * whiteSprite.getTexture()->getSize().x, 0.5f * whiteSprite.getTexture()->getSize().y});
		whiteSprite.setScale({flip * getSize().x / sprite.getTexture()->getSize().x, getSize().y / sprite.getTexture()->getSize().y});
		whiteSprite.setColor(sf::Color(255, 255, 255, 255));
		target.draw(whiteSprite);
	}
	else if((worldMousePos.x - sprite.getPosition().x) * (worldMousePos.x - sprite.getPosition().x) +
							   (worldMousePos.y - sprite.getPosition().y) * (worldMousePos.y - sprite.getPosition().y) < 6)
	{
		whiteSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
		whiteSprite.setOrigin({0.5f * whiteSprite.getTexture()->getSize().x, 0.5f * whiteSprite.getTexture()->getSize().y});
		whiteSprite.setScale({flip * getSize().x * 2.0f / sprite.getTexture()->getSize().x, getSize().y * 2.0f / sprite.getTexture()->getSize().y});
		whiteSprite.setColor(sf::Color(220, 220, 220, 255));
		target.draw(whiteSprite);
	}

	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});

	target.draw(sprite);
	target.draw(healthBar);

	if(!forest.getScreen().isDebug())
		return;

	drawDebug(target, states);
}

void Enemy::tick(float delta) {
	if(this->isDestroyed())
	{
		this->getForest().sendToCompost(this);
		return;
	}

	this->state->tick(delta);

	if(b2DistanceSquared(destination, getPosition()) < 1.f)
	{
		body->SetLinearVelocity({0.f, 0.f});
		return;
	}

	if(destinationChanged) {
		if(!getForest().getPathFinder().findPath(ENEMY_UNIT, getPosition(), destination, path))
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

b2Body* Enemy::getBody() const {
	return body;
}

b2Vec2 Enemy::getPosition() const {
	return body->GetPosition();
}

b2Vec2 Enemy::getSize() const {
	return b2Vec2(1.5f, 1.5f);
}

b2Vec2 Enemy::getDestination() const {
	return destination;
}

Forest& Enemy::getForest() {
	return forest;
}

float Enemy::getSpeed() const {
	return speed;
}

void Enemy::setSpeed(float speed) {
	this->speed = speed;
}

void Enemy::setFacingRight(bool facingRight) {
	this->facingRight = facingRight;
}

void Enemy::targetNearestTree() {
	if(forest.getAliveTrees().empty()) {
		this->state = std::make_shared<EnemyLeaveState>(this);
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

	Damageable* target = trees.front();
	setDestination(target->getPosition());

	this->state = std::make_shared<EnemyAttackState>(this, target);
}

void Enemy::targetNearestAnimal() {
    if(forest.getAnimals().empty()) {
        return;
    }

    std::vector<Animal*> animals(forest.getAnimals());

    if (animals.size() > 2) {
        std::sort(animals.begin(), animals.end(), [this](Animal* a, Animal* b){
            float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
            float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
            return a_dis < b_dis;
        });
    }

    Damageable* target = animals.front();
    setDestination(target->getPosition());

    this->state = std::make_shared<EnemyAttackState>(this, target);
}

std::shared_ptr<EnemyState> Enemy::getState() const {
	return state;
}

void Enemy::setState(std::shared_ptr<EnemyState> state) {
	Enemy::state = state;
}

void Enemy::setDestination(b2Vec2 destination) {
	Enemy::destination = destination;
	destinationChanged = true;
}

float Enemy::getZOrder() const {
	return -getPosition().y + 100;
}

bool Enemy::isLeaving() {
	return std::dynamic_pointer_cast<EnemyLeaveState>(state) != nullptr;
}

bool Enemy::isAttacking() {
    return std::dynamic_pointer_cast<EnemyAttackState>(state) != nullptr;
}

void Enemy::drawDebug(sf::RenderTarget& target, const sf::RenderStates& states) const {

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

const sf::Sprite &Enemy::getSprite() const {
    return sprite;
}

void Enemy::damage(Damager* attacker)  {
    Damageable::damage(attacker);

    if (!dynamic_cast<Animal*>(attacker))
        return;

    this->state = std::make_shared<EnemyAttackState>(this, dynamic_cast<Animal*>(attacker));
}
