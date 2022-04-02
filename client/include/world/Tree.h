//
// Created by cedric on 2022-04-02.
//

#ifndef LD50_TREE_H
#define LD50_TREE_H


#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Box2D/Dynamics/b2Body.h"

class Tree : public sf::Drawable {
    int health = 10;

	mutable sf::Sprite sprite;
	b2Body* body;
public:
    Tree(const wiz::AssetLoader& asset);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD50_TREE_H
