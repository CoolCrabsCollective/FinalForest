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

class Tree : public sf::Drawable, public Obstacle {
protected:
    int health = 10;

	mutable sf::Sprite sprite;
	b2Body* body;
	Forest& forest;
public:
    Tree(Forest& forest, b2Vec2 position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Body* getBody() const override;

	b2Vec2 getPosition() const override;

	b2Vec2 getSize() const override;

	Forest& getForest() const override;

	void setHealth(int health);

	bool isBlocking(b2Vec2 center, b2Vec2 size) override;
};


#endif //LD50_TREE_H
