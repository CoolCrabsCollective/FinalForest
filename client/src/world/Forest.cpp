//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Tree.h"
#include "world/Squirrel.h"
#include <stdlib.h>
#include <iostream>
#include "GameAssets.h"

Forest::Forest(const wiz::AssetLoader& assetLoader) : assetLoader(assetLoader), world(b2Vec2_zero) {

    nutCount = 0;
    grass_sprite[0] = sf::Sprite(*assetLoader.get(GameAssets::GRASS1));
    grass_sprite[1] = sf::Sprite(*assetLoader.get(GameAssets::GRASS2));
    grass_sprite[2] = sf::Sprite(*assetLoader.get(GameAssets::GRASS3));
    grass_sprite[3] = sf::Sprite(*assetLoader.get(GameAssets::GRASS4));

    float scale = grass_sprite->getScale().x / grass_sprite->getTexture()->getSize().x;
    for(int i = 0; i < 4; i++)
    {
        grass_sprite->setScale({scale, scale});
    }
    for(int i = 0; i < TILES_HEIGHT; i++)
    {
        for(int j = 0; j < TILES_WIDTH; j++)
        {
            grass_map[i][j] = rand() % 4;
        }
    }
    createForest();
}

Forest::~Forest() {
	for(Entity* entity : objects)
		delete entity;
	objects.clear();
}

void Forest::tick(float delta) {
	for(Entity* obj : objects) {
		Tickable* tickable = dynamic_cast<Tickable*>(obj);
		if(tickable)
			tickable->tick(delta);
	}

	world.Step(delta / 1000.0f, 6, 2);
}

void Forest::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	for(int i = 0; i < TILES_HEIGHT; i++)
    {
	    for(int j = 0; j < TILES_WIDTH; j++)
        {
            sf::Sprite grass = grass_sprite[grass_map[i][j]];
            grass.setPosition({j * 16.f, i * 16.f});
	        //target.draw(grass, states);
        }
    }

    for(Entity* obj : objects) {
		sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(obj);
		if(drawable)
			target.draw(*drawable, states);
	}
}

void Forest::createForest() {
    float minDistance = 8.f;
    int totalTrees = 75;
    std::vector<Tree *> trees;


    while (trees.size() < totalTrees) {
        float x = (float) (rand() % 100);
        float y = (float) (rand() % 100);
        b2Vec2 position(x, y);

        if(b2DistanceSquared(position, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f)
            continue;

        bool overlappingTree = false;
        for (Tree *tree : trees) {
            if (b2DistanceSquared(tree->getPosition(), position) < minDistance * minDistance) {
                overlappingTree = true;
                continue;
            }
        }

        if(!overlappingTree)
            trees.push_back(new Tree(*this, position));
    }

    for(Tree* tree : trees)
        objects.push_back(tree);



    objects.push_back(new Squirrel(*this, b2Vec2(0.0f, 0.0f)));
}

b2World& Forest::getB2World() {
	return world;
}

const wiz::AssetLoader& Forest::getAssets() const {
	return assetLoader;
}
