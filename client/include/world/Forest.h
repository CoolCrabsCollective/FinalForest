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
#include <unordered_map>

const float PATHFINDING_TILE_SIZE = 1.0f;

#define TILES_WIDTH 75
#define TILES_HEIGHT 50

class Forest : public sf::Drawable, public Tickable {
	const wiz::AssetLoader& assetLoader;
	b2World world;

	std::vector<Entity*> objects;

	mutable pf::PathFinder<ForestNode> pathFinder;
	std::unordered_map<uint32_t, ForestNode*> map;

    sf::Sprite grass_sprite[4];
    int grass_map[TILES_HEIGHT][TILES_WIDTH];
public:
    int nutCount;
    int squirrelCount;

	Forest(const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	void createForest();

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;

    void GenerateEnemyWave();

	void findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*> path) const;

private:
	ForestNode* getNode(b2Vec2 position) const;

	uint32_t key(b2Vec2 position) const;

};


#endif //LD50_CLIENT_FOREST_H
