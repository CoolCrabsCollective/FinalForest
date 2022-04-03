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
#include <world/state/SquirrelIdleState.h>
#include "GameAssets.h"
#include "world/BigAssTree.h"
#include "ForestScreen.h"
#include "world/River.h"
#include "world/MagicLake.h"

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
        grass_sprite[i].setScale({scale, scale});

    for(int i = 0; i < TILES_HEIGHT; i++)
        for(int j = 0; j < TILES_WIDTH; j++)
            grass_map[i][j] = rand() % 4;

    this->greatOakTree = new BigAssTree(*this, b2Vec2(50.0f, 50.0f));
	objects.push_back(this->greatOakTree);

	generateLakeAndRivers();
	generateForest();

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

    GenerateEnemyWave(20, 0.0);
}

Forest::~Forest() {
	for(Entity* entity : objects)
		delete entity;
	objects.clear();
}

void Forest::spawnSquirrel() {
    Squirrel* squirrel = new Squirrel(*this, {50, 50});
    objects.push_back(squirrel);
    assignToNextAvailableTree(squirrel);
}

void Forest::assignToNextAvailableTree(Squirrel* squirrel) {
    Tree* tree = getNextAvailableTree();
    if(tree) {
        assignSquirrel(squirrel, tree);
        squirrel->setState(std::make_shared<SquirrelGoGatherState>(this, squirrel, tree));
    } else
        squirrel->setState(std::make_shared<SquirrelIdleState>(this, squirrel));
}

void Forest::assignSquirrel(Squirrel *squirrel, Tree *tree) {
    squirrelTreeMap.insert(std::pair<Squirrel*, Tree*> {squirrel, tree});
    treeSquirrelMap.insert(std::pair<Tree*, Squirrel*> {tree, squirrel});
}

void Forest::reAssignTree(Tree *tree) {
    if (treeSquirrelMap.contains(tree)) {
        Squirrel* squirrel = treeSquirrelMap[tree];
        unassignTree(tree);
        assignToNextAvailableTree(squirrel);
    }
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

void Forest::killTree(Tree* tree) {
    for (int i = 0; i<aliveTrees.size(); i++) {
        if (aliveTrees.at(i) == tree) {
            aliveTrees.erase(aliveTrees.begin() + i);
        }
    }
    reAssignTree(tree);
}

Tree *Forest::getNextAvailableTree() {
    for(Tree* tree : aliveTrees)
        if(!dynamic_cast<BigAssTree*>(tree) && !treeSquirrelMap.contains(tree))
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

void Forest::GenerateEnemyWave(int numOfEnemies, float difficulty) {
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

	if(getScreen().isDebug())
		finder.draw(target, states);

	renderables.clear();

	for(Entity* obj : objects) {
		Renderable* renderable = dynamic_cast<Renderable*>(obj);
		if(renderable)
			renderables.push_back(renderable);
	}

	std::sort(renderables.begin(), renderables.end(), [&](Renderable* a, Renderable* b){
		return a->getZOrder() > b->getZOrder();
	});

    for(Renderable* renderable : renderables)
		target.draw(*renderable);
}

void Forest::generateForest() {
    int totalTrees = 55;
	int addedTrees = 0;
	int i = 1000;

    while (addedTrees < totalTrees) {
		if(i-- < 0) {
			getScreen().getLogger().error("Failed to generate entire forest after 1 000 iterations");
			break;
		}
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
			MagicLake* lake = dynamic_cast<MagicLake*>(entity);
			if(river || lake) {
				if(dynamic_cast<Obstacle*>(entity)->isBlocking(position, { 5.0f, 10.0f })) {
					overlapping = true;
					continue;
				}
			}

			float minDistance;

			if(dynamic_cast<BigAssTree*>(entity))
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

void Forest::generateLakeAndRivers() {

	float deg = (float) (rand() % 360);

	sf::Vector2f vec(25.0f, 0.0f);
	vec = vec.rotatedBy(sf::degrees(deg));

	MagicLake* lake = new MagicLake(*this, b2Vec2(vec.x + 50.0f, vec.y + 50.0f));
	objects.push_back(lake);

	int countRiver = rand() % 3 + 1;

	std::vector<River*> rivers;

	for(int i = 0; i < 1; i++) {

		float deg = (float) (rand() % 360);

		sf::Vector2f vec(60.0f, 0.0f);
		vec = vec.rotatedBy(sf::degrees(deg));

		std::vector<b2Vec2> path;
		b2Vec2 start(vec.x + 50.0f, vec.y + 50.0f);
		path.push_back(start);

		sf::Vector2f initialDir = vec.normalized() * 5.0f;

		path.push_back(start - b2Vec2(initialDir.x, initialDir.y));
		b2Vec2 current = path[path.size() - 1];

		int tries = 1000;
		while(current.x > -10.0f && current.y > -10.0f && current.x < 110.0f && current.y < 110.0f) {
			if(tries-- < 0) {
				getScreen().getLogger().error("Failed to generate river part after 1 000 iterations");
				break;
			}

			float deg = (float) (rand() % 360);

			sf::Vector2f vec(5.0f, 0.0f);
			vec = vec.rotatedBy(sf::degrees(deg));

			current += b2Vec2(vec.x, vec.y);

			b2Vec2 dir = (current - path[path.size() - 1]);
			dir.Normalize();

			b2Vec2 prevDir = path[path.size() - 1] - path[path.size() - 2];
			prevDir.Normalize();

			float dot = b2Dot(dir, prevDir);

			if(dot < 0.7f)
				continue;

			if(River::isBlocking(path, 4.0f, current, b2Vec2_zero))
				continue;

			if(lake->isBlocking(current, b2Vec2_zero)) {
				current = lake->getPosition();
				path.push_back(current);
				break;
			}

			path.push_back(current);
		}


		getScreen().getLogger().info("Parts: " + std::to_string(path.size()));
		objects.push_back(new River(*this, path, 4.0f));
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

BigAssTree* Forest::getGreatOakTree() const {
    return greatOakTree;
}