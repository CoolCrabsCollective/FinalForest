//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/tree/Tree.h"
#include "world/animal/Squirrel.h"
#include "world/enemy/LumberJack.h"
#include <iostream>
#include <memory>
#include "world/animal/state/SquirrelGoGathertState.h"
#include "world/animal/state/AnimalIdleState.h"
#include <world/NutShot.h>
#include "GameAssets.h"
#include "world/tree/BigAssTree.h"
#include "ForestScreen.h"
#include "world/water/River.h"
#include "world/water/MagicLake.h"
#include "world/animal/Wolf.h"
#include "world/animal/Bear.h"

Forest::Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader)
	: screen(screen),
		assetLoader(assetLoader),
		world(b2Vec2_zero),
		finder(screen.getLogger(), assetLoader)
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
		if(dynamic_cast<Tree*>(entity))
			trees.push_back(dynamic_cast<Tree*>(entity));

	std::sort(trees.begin(), trees.end(), [&](Tree* a, Tree* b){
		b2Vec2 bigTree = {this->getGreatOakTree()->getPosition().x, this->getGreatOakTree()->getPosition().y};
		float a_dis = b2DistanceSquared(a->getPosition(), bigTree);
		float b_dis = b2DistanceSquared(b->getPosition(), bigTree);
		return a_dis < b_dis;
	});

    aliveTrees = std::vector<Tree*>(trees);

	finder.initialize(objects);

	for(Entity* entity : objects) {
		River* river = dynamic_cast<River*>(entity);

		if(!river)
			continue;

		const std::vector<b2Vec2>& path = river->getPath();
		for(size_t i = 1; i < path.size(); i++) {

			float dst1 = b2DistanceSquared(path[i - 1], b2Vec2(50.0f, 50.0f));
			float dst2 = b2DistanceSquared(path[i], b2Vec2(50.0f, 50.0f));

			if(dst1 < 60.0f * 60.0f && dst2 > 60.0f * 60.0f
			   || dst1 > 60.0f * 60.0f && dst2 < 60.0f * 60.0f)
				river->addBridge(new Bridge(*river, i, METAL));
		}
	}

    generateEnemyWave(20, 0.0);

    for(int i = 0; i < 8; i++)
        spawnSquirrel();
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

void Forest::spawnWolf() {
	Wolf* wolf = new Wolf(*this, {50, 50});
	objects.push_back(wolf);
	wolf->targetNearestEnemy();
}

void Forest::spawnBear() {
	Bear* bear = new Bear(*this, {50, 50});
	objects.push_back(bear);
	bear->targetNearestEnemy();
}

void Forest::assignToNextAvailableTree(Squirrel* squirrel) {
    Tree* tree = getNextAvailableTree();
    if(tree) {
        assignSquirrel(squirrel, tree);
        squirrel->setState(std::make_shared<SquirrelGoGatherState>(squirrel, tree));
    } else
        squirrel->setState(std::make_shared<AnimalIdleState>(squirrel));
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
		Tickable* tickable = dynamic_cast<Tickable*>(obj);
		if(tickable)
			tickable->tick(delta);
	}

	for(Entity* trash : toDelete)
    {
        if (trash->numberOfTicksAfterDeletion < 1) {
            trash->numberOfTicksAfterDeletion++;
            continue;
        }
	    std::vector<Entity*>::iterator entity_it = std::find(objects.begin(), objects.end(), trash);
	    objects.erase(entity_it);
	    if(dynamic_cast<Enemy*>(*entity_it))
        {
            std::vector<Enemy*>::iterator enemy_it = std::find(enemies.begin(), enemies.end(), trash);
	        enemies.erase(enemy_it);
        }

	    if(trash == getScreen().getSelectedTree())
	        getScreen().setSelectedTree(nullptr);

	    //delete trash;
    }

	toDelete.clear();

	world.Step(delta / 1000.0f, 6, 2);
}

void Forest::generateEnemyWave(int numOfEnemies, float difficulty) {
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

        LumberJack* lumberJack = new LumberJack(*this, b2Vec2(newXPos, newYPos));
        objects.push_back(lumberJack);
        enemies.push_back(lumberJack);
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
		return a->getZOrder() < b->getZOrder();
	});

    for(Renderable* renderable : renderables)
		target.draw(*renderable);
}

void Forest::generateForest() {
	int noLuck = 0;

    while (noLuck < 50) {
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
			noLuck = 0;
		}
		noLuck++;
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

	for(int i = 0; i < countRiver; i++) {

		bool noInside = true;
		float deg = (float) (rand() % 360);

		sf::Vector2f vec(100.0f, 0.0f);
		vec = vec.rotatedBy(sf::degrees(deg));

		if(abs(vec.x) > abs(vec.y)) {
			if(vec.x > 0)
				vec.x = 105.0f;
			else
				vec.x = -105.0f;
		} else {
			if(vec.y > 0)
				vec.y = 105.0f;
			else
				vec.y = -105.0f;
		}

		std::vector<b2Vec2> path;
		b2Vec2 start(vec.x + 50.0f, vec.y + 50.0f);
		path.push_back(start);

		sf::Vector2f initialDir = vec.normalized() * 5.0f;

		path.push_back(start - b2Vec2(initialDir.x, initialDir.y));
		b2Vec2 current = path[path.size() - 1];

		int tries = 100;
		while(current.x > -60.0f && current.y > -60.0f && current.x < 160.0f && current.y < 160.0f) {
			if(tries-- < 0) {
				noInside = true;
				break;
			}

			float baseDst = b2DistanceSquared(path[path.size() - 1], b2Vec2(50.0f, 50.0f));
			if(baseDst < 40.0f * 40.0f)
				noInside = false;

			float deg = (float) (rand() % 360);

			sf::Vector2f vec(5.0f, 0.0f);
			vec = vec.rotatedBy(sf::degrees(deg));

			current = path[path.size() - 1] + b2Vec2(vec.x, vec.y);

			b2Vec2 dir = (current - path[path.size() - 1]);
			dir.Normalize();

			b2Vec2 prevDir = path[path.size() - 1] - path[path.size() - 2];
			prevDir.Normalize();

			float dot = b2Dot(dir, prevDir);

			if(dot < 0.7f)
				continue;

			float treeDst = b2DistanceSquared(greatOakTree->getPosition(), current);
			if(treeDst < 15.0f * 15.0f)
				continue;

			if(River::isBlocking(path, 4.0f, current, b2Vec2(4.0f, 4.0f)))
				continue;

			if(lake->isBlocking(current, b2Vec2(4.0f, 4.0f))) {
				current = lake->getPosition();
				path.push_back(current);
				break;
			}

			for(River* river : rivers) {

				b2Vec2 closest = river->getPath()[0];

				for(b2Vec2 node : river->getPath()) {
					if(b2DistanceSquared(node, current) < b2DistanceSquared(closest, current)) {
						closest = node;
					}
				}

				if(b2DistanceSquared(closest, current) < 5.0f * 5.0f) {
					current = closest;
					path.push_back(current);
					break;
				}
			}

			path.push_back(current);
		}

		if(noInside) {
			i--;
			continue;
		}

		River* river = new River(*this, path, path.size() < 10 ? 3.0f : 4.0f);
		rivers.push_back(river);
		objects.push_back(river);
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

ForestScreen& Forest::getScreen() {
    return const_cast<ForestScreen &>(screen);
}

const ForestPathFinder& Forest::getPathFinder() const {
	return finder;
}

ForestPathFinder& Forest::getPathFinder() {
	return finder;
}

BigAssTree* Forest::getGreatOakTree() const {
    return greatOakTree;
}

const std::vector<Enemy *> &Forest::getEnemies() const {
    return enemies;
}

void Forest::shootNut(NutShot *nut) {
    objects.push_back(nut);
}

void Forest::sendToCompost(Entity* entity) {
    this->toDelete.push_back(entity);
}

const std::vector<Entity *> &Forest::getToDelete() const {
    return toDelete;
}

const std::vector<Entity *> &Forest::getObjects() const {
    return objects;
}

