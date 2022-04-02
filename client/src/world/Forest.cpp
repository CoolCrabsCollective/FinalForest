//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Tree.h"
#include "world/Squirrel.h"
#include "world/LumberJack.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "GameAssets.h"
#include "world/BigAssTree.h"

Forest::Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader)
	: screen(screen),
		assetLoader(assetLoader),
		world(b2Vec2_zero),
		map() {

    nutCount = 0;
    squirrelCount = 0;

    grass_sprite[0] = sf::Sprite(*assetLoader.get(GameAssets::GRASS1));
    grass_sprite[1] = sf::Sprite(*assetLoader.get(GameAssets::GRASS2));
    grass_sprite[2] = sf::Sprite(*assetLoader.get(GameAssets::GRASS3));
    grass_sprite[3] = sf::Sprite(*assetLoader.get(GameAssets::GRASS4));


    float scale = grass_sprite->getScale().x / grass_sprite->getTexture()->getSize().x * 3;
    for(int i = 0; i < 4; i++)
    {
        grass_sprite[i].setScale({scale, scale});
    }

    for(int i = 0; i < TILES_HEIGHT; i++)
        for(int j = 0; j < TILES_WIDTH; j++)
            grass_map[i][j] = rand() % 4;

	objects.push_back(new BigAssTree(*this, b2Vec2(50.0f, 50.0f)));

    createForest();

	objects.push_back(new Squirrel(*this, b2Vec2(0.0f, 0.0f)));

	int16_t minX = floor(-50.0f / PATHFINDING_TILE_SIZE);
	int16_t minY = floor(-50.0f / PATHFINDING_TILE_SIZE);

	int16_t maxX = floor(50.0f / PATHFINDING_TILE_SIZE);
	int16_t maxY = floor(50.0f / PATHFINDING_TILE_SIZE);

	for(int16_t x = minX; x < maxX; x++) {
		for(int16_t y = minY; y < maxY; y++) {
			uint32_t key = x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);

			ForestNode* node = new ForestNode();


			node->setPosition(x, y);

			map[key] = node;
		}
	}

    GenerateEnemyWave(20);
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

void Forest::GenerateEnemyWave(int numOfEnemies) {
    int spawnRadius;
    int screenCenter = 50;

    int spawnDirection;
    float newXPos;
    float newYPos;

    for (int i = 0; i<numOfEnemies; i++) {
        spawnRadius = rand() % 150 + 80;

        spawnDirection = rand() % 360;

        newXPos = (float) cos( spawnDirection * M_PI / 180.0 ) * spawnRadius + screenCenter;

        newYPos = (float) sin( spawnDirection * M_PI / 180.0 ) * spawnRadius + screenCenter;

        objects.push_back(new LumberJack(*this, b2Vec2(newXPos, newYPos)));
    }
}

void Forest::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	for(int i = 0; i < TILES_HEIGHT; i++)
    {
	    for(int j = 0; j < TILES_WIDTH; j++)
        {
            sf::Sprite grass = grass_sprite[grass_map[i][j]];
            grass.setPosition({-60 + j * 16.f * grass_sprite->getScale().x, -10 + i * 16.f * grass_sprite->getScale().y});
	        target.draw(grass, states);
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
    int totalTrees = 55;
	int addedTrees = 0;

    while (addedTrees < totalTrees) {
        float x = (float) (rand() % 100);
        float y = (float) (rand() % 100);
        b2Vec2 position(x, y);

        if(b2DistanceSquared(position, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f)
            continue;

        bool overlapping = false;
        for (Entity* entity : objects) {
			Physical* physical = dynamic_cast<Physical*>(entity);

			if(!physical)
				continue;

			float minDistance;

			if(dynamic_cast<BigAssTree*>(entity))
				minDistance = (physical->getSize().x + physical->getSize().y) / 2.0f;
			else
				minDistance = (physical->getSize().x + physical->getSize().y) * 3.0f / 4.0f;

            if(b2DistanceSquared(physical->getPosition(), position) < minDistance * minDistance) {
				overlapping = true;
                continue;
            }
        }

        if(!overlapping) {
			objects.push_back(new Tree(*this, position));
			addedTrees++;
		}
    }
}

b2World& Forest::getB2World() {
	return world;
}

const wiz::AssetLoader& Forest::getAssets() const {
	return assetLoader;
}

void Forest::findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*> path) const {
	pathFinder.setStart(*getNode(start));
	pathFinder.setGoal(*getNode(goal));

	if(!pathFinder.findPath<pf::AStar>(path))
		path.clear();
}

ForestNode* Forest::getNode(b2Vec2 position) const {
	return map.at(key(position));
}

uint32_t Forest::key(b2Vec2 position) const {
	int16_t x = static_cast<int16_t>(floor(position.x / PATHFINDING_TILE_SIZE));
	int16_t y = static_cast<int16_t>(floor(position.y / PATHFINDING_TILE_SIZE));

	return x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);
}

const ForestScreen& Forest::getScreen() const {
	return screen;
}
