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
#include <math.h>

Forest::Forest(const wiz::AssetLoader& assetLoader) : assetLoader(assetLoader),
		world(b2Vec2_zero),
		map() {

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

	for(Entity* obj : objects) {
		sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(obj);
		if(drawable)
			target.draw(*drawable, states);
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
