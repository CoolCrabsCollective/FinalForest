//
// Created by Sir Dick on 2022-04-02.
//

#ifndef LD50_TREE_H
#define LD50_TREE_H


#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Box2D/Dynamics/b2Body.h"
#include "world/Forest.h"
#include "world/Obstacle.h"
#include "world/Renderable.h"
#include "world/Damageable.h"
#include "world/HealthBar.h"

#define TIME_FOR_NUTSHOT 2.f
class Tree : public Renderable, public Obstacle, public Damageable, public Tickable {
protected:
    mutable sf::Sprite sprite;
    mutable sf::Sprite whiteTreeSprite;

    sf::Texture* normalTreeTexture;
    sf::Texture* turretTreeTexture;

    sf::Text labelSquirrelCount;

	b2Body* body;
	Forest& forest;
	int squirrels = 0;
	float timeLeftForNut;
	b2Fixture* fixture;

    HealthBar healthBar;

public:
    Tree(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	Forest& getForest() override;

	void addSquirrelTurret();

    void removeSquirrelTurret();

    int getSquirrelCount() const;

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;

	float getZOrder() const override;

    void tick(float delta) override;

	void damage(Damager* attacker) override;

    const sf::Sprite &getSprite() const;
};


#endif //LD50_TREE_H
