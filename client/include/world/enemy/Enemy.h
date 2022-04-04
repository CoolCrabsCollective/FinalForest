//
// Created by Cedric on 2022-04-03.
//

#ifndef LD50_COMMON_ENEMY_H
#define LD50_COMMON_ENEMY_H


#include "world/Renderable.h"
#include "world/Physical.h"
#include "world/Tickable.h"
#include "world/Damageable.h"
#include "world/Damager.h"
#include "world/Anime.h"
#include "world/pathfinding/ForestNode.h"
#include "world/enemy/state/EnemyState.h"
#include "world/HealthBar.h"

class Enemy : virtual public Renderable, virtual public Physical, virtual public Tickable, virtual public Damageable, virtual public Damager, virtual public Anime {
protected:
	b2Body* body;

	std::vector<ForestNode*> path;
	int pathIndex = -1;
	b2Vec2 destination = b2Vec2(50.0f, 50.0f);
	bool destinationChanged = false;

	float speed = 10.0f;
	bool facingRight = false;

	std::shared_ptr<EnemyState> state;
	Forest& forest;
	mutable sf::Sprite sprite, whiteSprite, debugSprite;
	HealthBar healthBar;
public:
	Enemy(Forest& forest, b2Vec2 position);

	std::shared_ptr<EnemyState> getState() const;

	void setState(std::shared_ptr<EnemyState> state);

	Forest& getForest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	b2Vec2 getDestination() const;

	void setDestination(b2Vec2 destination);

	float getSpeed() const;

	void setSpeed(float speed);

	void setFacingRight(bool facingRight);

	void targetNearestTree();

    void targetNearestAnimal();

	void tick(float delta) override;

	float getZOrder() const override;

	bool isLeaving();

    bool isAttacking();

	void drawDebug(sf::RenderTarget& target, const sf::RenderStates& states) const;

    const sf::Sprite &getSprite() const;

    void damage(Damager* attacker) override;
};


#endif //LD50_COMMON_ENEMY_H
