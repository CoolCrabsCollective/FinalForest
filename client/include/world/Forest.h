//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FOREST_H
#define LD50_CLIENT_FOREST_H


#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"
#include "WIZ/asset/AssetLoader.h"
#include "Dynamics/b2World.h"
#include "Entity.h"
#include "PathFinder/AStar.h"
#include "PathFinder/PathFinder.h"
#include "SFML/System/Vector2.hpp"
#include "ForestNode.h"
#include <unordered_map>

const float PATHFINDING_TILE_SIZE = 1.0f;

class Forest : public sf::Drawable, public Tickable {
	const wiz::AssetLoader& assetLoader;
	b2World world;

	std::vector<Entity*> objects;

	mutable pf::PathFinder<ForestNode> pathFinder;

	std::unordered_map<uint32_t, ForestNode*> map;
public:
	Forest(const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;

	void findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*> path) const;

private:
	ForestNode* getNode(b2Vec2 position) const;

	uint32_t key(b2Vec2 position) const;
};


#endif //LD50_CLIENT_FOREST_H
