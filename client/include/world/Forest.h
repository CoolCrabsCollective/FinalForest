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
#include "WIZ/game/Screen.h"
#include <unordered_map>
#include "world/pathfinding/ForestPathFinder.h"

class ForestScreen;

#define TILES_WIDTH 75
#define TILES_HEIGHT 50

#define PI 3.14159265

class Forest : public sf::Drawable, public Tickable {
	const ForestScreen& screen;
	const wiz::AssetLoader& assetLoader;
	b2World world;

	std::vector<Entity*> objects;

	ForestPathFinder finder;

    sf::Sprite grass_sprite[4];
    int grass_map[TILES_HEIGHT][TILES_WIDTH];
public:
    int nutCount;
    int squirrelCount;

	Forest(const ForestScreen& screen, const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void createForest();

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;

    void GenerateEnemyWave(int numOfEnemies);

	const ForestPathFinder& getPathFinder() const;

	const ForestScreen& getScreen() const;
};


#endif //LD50_CLIENT_FOREST_H
