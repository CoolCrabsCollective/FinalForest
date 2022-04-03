//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_TREE_H
#define LD50_TREE_H


#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Forest.h"
#include "Obstacle.h"
#include "Renderable.h"
#include "Damageable.h"

#define TIME_FOR_NUTSHOT 2.f
class Tree : public Renderable, public Obstacle, public Damageable, public Tickable {
protected:
    mutable sf::Sprite sprite;

	b2Body* body;
	Forest& forest;
	std::vector<Squirrel*> squirrels;
	float timeLeftForNut;

public:
    Tree(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	Forest& getForest() const override;

	void addSquirrelTurret(Squirrel* squirrel);

    int getSquirrelCount();

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;

	float getZOrder() const override;

    void tick(float delta) override;
};


#endif //LD50_TREE_H
