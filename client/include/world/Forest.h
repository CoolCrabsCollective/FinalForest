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
#include "world/pathfinding/ForestNode.h"
#include "Squirrel.h"
#include "Tree.h"
#include "WIZ/game/Screen.h"
#include <unordered_map>
#include "world/pathfinding/ForestPathFinder.h"
#include <math.h>
#include "world/Enemy.h"
#include "world/NutShot.h"

class ForestScreen;
class Tree;
class Squirrel;
class BigAssTree;
class NutShot;

#define TILES_WIDTH 75
#define TILES_HEIGHT 50

enum Currency {Nuts, Mana};

class Forest : public sf::Drawable, public Tickable {
private:
    ForestPathFinder finder;

    sf::Sprite grass_sprite[4];
    BigAssTree* greatOakTree;
    int grass_map[TILES_HEIGHT][TILES_WIDTH];
    std::map<Squirrel*, Tree*> squirrelTreeMap;
    std::map<Tree*, Squirrel*> treeSquirrelMap;

    std::vector<Entity*> toDelete;

public:
    int nutCount;
    int squirrelCount;
    int mana;

    const ForestScreen& screen;
    const wiz::AssetLoader& assetLoader;
    b2World world;

    std::vector<Entity*> objects;
    mutable std::vector<Renderable*> renderables;
    std::vector<Tree*> trees;
    std::vector<Tree*> aliveTrees;
    std::vector<Enemy*> enemies;

	Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void generateForest();

	void spawnSquirrel();

    void assignToNextAvailableTree(Squirrel* squirrel);

	void assignSquirrel(Squirrel* squirrel, Tree* tree);

	Tree* getNextAvailableTree();

    void reAssignTree(Tree *tree);

    void unassignTree(Tree* tree);

    void unassignSquirrel(Squirrel* squirrel);

    void killTree(Tree* tree);

    void shootNut(NutShot* nut);

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;

    void GenerateEnemyWave(int numOfEnemies, float difficulty);

	const ForestPathFinder& getPathFinder() const;

	const ForestScreen& getScreen() const;

	BigAssTree* getGreatOakTree() const;

    const std::vector<Tree*> getAliveTrees() const;

	void generateLakeAndRivers();

    const std::vector<Enemy *> &getEnemies() const;

    void sendToCompost(Entity* entity);
};


#endif //LD50_CLIENT_FOREST_H
