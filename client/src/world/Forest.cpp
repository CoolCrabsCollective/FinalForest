//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Tree.h"
#include "world/Squirrel.h"
#include "world/LumberJack.h"
#include "world/LumberJackChainsaw.h"
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <math.h>
#include <world/state/SquirrelGoGathertState.h>
#include "GameAssets.h"
#include "world/AssTree.h"
#include "ForestScreen.h"
#include "world/River.h"

Forest::Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader)
	: screen(screen),
		assetLoader(assetLoader),
		world(b2Vec2_zero),
		finder(assetLoader)
{
    nutCount = 0;
    squirrelCount = 0;
    mana = 0;

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

    this->greatOakTree = new AssTree(*this, b2Vec2(50.0f, 50.0f));
	objects.push_back(this->greatOakTree);

	objects.push_back(new River(*this, { b2Vec2(-50.0f, -50.0f),
										 b2Vec2(20.0f, 20.0f),
										 b2Vec2(20.0f, 25.0f),
										 b2Vec2(25.0f, 30.0f),
										 b2Vec2(30.0f, 25.0f),
										 b2Vec2(40.0f, 25.0f),
										 b2Vec2(45.0f, 30.0f),
										 b2Vec2(50.0f, 30.0f),
										 b2Vec2(55.0f, 25.0f),
										 b2Vec2(60.0f, 25.0f),
										 b2Vec2(65.0f, 20.0f),
										 b2Vec2(70.0f, 15.0f),
										 b2Vec2(75.0f, 10.0f),
										 b2Vec2(75.0f, 5.0f),
										 b2Vec2(80.0f, 0.0f),
										 b2Vec2(85.0f, -5.0f),
										 b2Vec2(120.0f, -40.0f)}, 2.0f));

    createForest();

	for(Entity* entity : objects)
	{
		if(dynamic_cast<Tree*>(entity))
			trees.push_back(dynamic_cast<Tree*>(entity));
	}

	std::sort(trees.begin(), trees.end(), [&](Tree* a, Tree* b){
		b2Vec2 bigTree = {this->getGreatOakTree()->getPosition().x, this->getGreatOakTree()->getPosition().y};
		float a_dis = b2DistanceSquared(a->getPosition(), bigTree);
		float b_dis = b2DistanceSquared(b->getPosition(), bigTree);
		return a_dis < b_dis;
	});

    aliveTrees = std::vector<Tree*>(trees);

	for(int i = 0; i < 8; i++)
		spawnSquirrel();

	finder.initialize(objects);

    GenerateEnemyWave(20);
}

Forest::~Forest() {
	for(Entity* entity : objects)
		delete entity;
	objects.clear();
}


void Forest::spawnSquirrel() {
    Squirrel* squirrel = new Squirrel(*this, {50, 50});
    objects.push_back(squirrel);
    Tree* tree = getNextAvailableTree();
    if(tree) {
        assignSquirrel(squirrel, tree);
        squirrel->setState(std::make_shared<SquirrelGoGatherState>(this, squirrel, tree));
    }
}

void Forest::assignSquirrel(Squirrel *squirrel, Tree *tree) {
    squirrelTreeMap.insert(std::pair<Squirrel*, Tree*> {squirrel, tree});
    treeSquirrelMap.insert(std::pair<Tree*, Squirrel*> {tree, squirrel});
}

void Forest::unassignTree(Tree *tree) {
    Squirrel* squirrel = treeSquirrelMap[tree];
    treeSquirrelMap.erase(tree);
    squirrelTreeMap.erase(squirrel);
}

void Forest::unassignSquirrel(Squirrel *squirrel) {
    Tree* tree = squirrelTreeMap[squirrel];
    squirrelTreeMap.erase(squirrel);
    treeSquirrelMap.erase(tree);
}

Tree *Forest::getNextAvailableTree() {
    for(Tree* tree : aliveTrees)
        if(!dynamic_cast<AssTree*>(tree) && !treeSquirrelMap.contains(tree))
            return tree;

    return nullptr;
}


void Forest::tick(float delta) {
    for(Entity* obj : objects) {
        Squirrel* squirrel = dynamic_cast<Squirrel*>(obj);
        if(squirrel)
            squirrel->getState()->tick(delta);
    }

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

        objects.push_back(new LumberJackChainsaw(*this, b2Vec2(newXPos, newYPos)));
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

	if(getScreen().isDebug())
		finder.draw(target, states);

    for(Entity* obj : objects) {
		sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(obj);
		if(drawable)
			target.draw(*drawable, states);
	}
}

void Forest::createForest() {
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

			River* river = dynamic_cast<River*>(entity);
			if(river) {
				if(river->isBlocking(position, { 5.0f, 5.0f })) {
					overlapping = true;
					continue;
				}
			}

			float minDistance;

			if(dynamic_cast<AssTree*>(entity))
				minDistance = (physical->getSize().x + physical->getSize().y) / 2.0f;
			else if(dynamic_cast<Tree*>(entity))
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

const std::vector<Tree*> Forest::getAliveTrees() const {
    return aliveTrees;
}

const wiz::AssetLoader& Forest::getAssets() const {
	return assetLoader;
}

const ForestScreen& Forest::getScreen() const {
	return screen;
}

const ForestPathFinder& Forest::getPathFinder() const {
	return finder;
}

AssTree* Forest::getGreatOakTree() const {
    return greatOakTree;
}
