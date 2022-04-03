//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FORESTPATHFINDER_H
#define LD50_CLIENT_FORESTPATHFINDER_H

#include "ForestNode.h"
#include "Box2D/Common/b2Math.h"
#include "PathFinder/PathFinder.h"
#include "world/Entity.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "WIZ/asset/AssetLoader.h"

class ForestPathFinder : public sf::Drawable {

	mutable sf::Sprite debugSprite;

	mutable pf::PathFinder<ForestNode> pathFinder;
	std::unordered_map<uint32_t, ForestNode*> map;
public:
	ForestPathFinder(const wiz::AssetLoader& assets);

	void initialize(const std::vector<Entity*>& vec);

	bool findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*>& path) const;

	b2Vec2 getTileSize() const;

	b2Vec2 getTileStart() const;

	sf::Vector2i worldToTileCoordinates(b2Vec2 worldCoords) const;

	b2Vec2 tileToWorldCoordinates(sf::Vector2i worldCoords) const;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

private:
	ForestNode* getNode(b2Vec2 position) const;

	uint32_t keyOf(b2Vec2 position) const;

	uint32_t keyOf(sf::Vector2i tile) const;
};


#endif //LD50_CLIENT_FORESTPATHFINDER_H
