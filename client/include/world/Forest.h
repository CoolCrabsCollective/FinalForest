//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FOREST_H
#define LD50_CLIENT_FOREST_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Box2D/Dynamics/b2World.h"
#include "Entity.h"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "SFML/System/Vector2.hpp"
#include "ForestNode.h"
#include "Squirrel.h"
#include "Tree.h"
#include "WIZ/game/Screen.h"
#include <unordered_map>
#include <math.h>

class ForestScreen;
class Tree;
class Squirrel;
class GreatOakTree;

const float PATHFINDING_TILE_SIZE = 1.0f;

#define TILES_WIDTH 75
#define TILES_HEIGHT 50

class Forest : public sf::Drawable, public Tickable {
	const ForestScreen& screen;
	const wiz::AssetLoader& assetLoader;
	b2World world;

	std::vector<Entity*> objects;
	std::vector<Tree*> trees;

	mutable pf::PathFinder<ForestNode> pathFinder;
	std::unordered_map<uint32_t, ForestNode*> map;

    sf::Sprite grass_sprite[4];
    GreatOakTree* greatOakTree;
    int grass_map[TILES_HEIGHT][TILES_WIDTH];
    std::map<Squirrel*, Tree*> squirrelTreeMap;
    std::map<Tree*, Squirrel*> treeSquirrelMap;
public:
    int nutCount;
    int squirrelCount;
    int mana;

	Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void createForest();

	void spawnSquirrel();
	void assignSquirrel(Squirrel* squirrel, Tree* tree);
	Tree* getNextAvailableTree();
    void unassignTree(Tree* tree);
    void unassignSquirrel(Squirrel* squirrel);

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;

    void GenerateEnemyWave(int numOfEnemies);

	void findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*> path) const;

	const ForestScreen& getScreen() const;

	GreatOakTree* getGreatOakTree() const;

    const std::vector<Tree*> getTrees() const;

private:
	ForestNode* getNode(b2Vec2 position) const;

	uint32_t key(b2Vec2 position) const;

};


#endif //LD50_CLIENT_FOREST_H
