//
// Created by Alexander Winter🤤 on 2022-04-02.
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
#include "world/animal/Squirrel.h"
#include "world/tree/Tree.h"
#include "WIZ/game/Screen.h"
#include <unordered_map>
#include "world/pathfinding/ForestPathFinder.h"
#include <math.h>
#include "world/enemy/Enemy.h"
#include "world/NutShot.h"
#include "world/definitions/WaveSpawnGetter.h"

class ForestScreen;
class Tree;
class Squirrel;
class BigAssTree;
class NutShot;

enum Currency {Nuts, Mana};

struct WaveState {
    unsigned int round = 1;
    float difficulty = 1.0;
    int secondsBetweenWaves = 5;
};

class Forest : public sf::Drawable, public Tickable {
    ForestPathFinder finder;

	sf::Sprite grassSprite;

    BigAssTree* greatOakTree;
    std::map<Squirrel*, Tree*> squirrelTreeMap;
    std::map<Tree*, Squirrel*> treeSquirrelMap;

    std::vector<Entity*> toDelete;

    WaveSpawnGetter waveSpawnGetter;

public:
    int nutCount;
    int squirrelCount;

    int getSquirrelCount() const;

    int mana;

    const ForestScreen& screen;
    const wiz::AssetLoader& assetLoader;
    b2World world;

    std::vector<Entity*> objects;

    const std::vector<Entity *> &getObjects() const;

    mutable std::vector<Renderable*> renderables;
    std::vector<Tree*> trees;
    std::vector<Tree*> aliveTrees;
    std::vector<Enemy*> enemies;
    std::vector<Animal*> animals;

    WaveState waveState;

	Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void generateForest();

	void spawnSquirrel();

	void respawnSquirrel(Tree* tree);

	void spawnWolf();

	void spawnBear();

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

    void generateEnemyWave();

    b2Vec2 getRandomEnemySpawn();

	b2Vec2 getRandomEnemySpawn(float spawnDir);

	const ForestPathFinder& getPathFinder() const;

	ForestPathFinder& getPathFinder();

	const ForestScreen& getScreen() const;

	ForestScreen& getScreen();

    BigAssTree* getGreatOakTree() const;

    const std::vector<Tree*> getAliveTrees() const;

	void generateLakeAndRivers();

    const std::vector<Enemy *> &getEnemies() const;

    void sendToCompost(Entity* entity);

    const std::vector<Entity *> &getToDelete() const;

    const std::vector<Animal *> &getAnimals() const;

    int availableSquirrelsCount();

    int availableWolvesCount();

    int availableBearsCount();
};


#endif //LD50_CLIENT_FOREST_H
