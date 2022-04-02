//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Physical.h"
#include "world/pathfinding/ForestPathFinder.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Obstacle.h"


void ForestPathFinder::initialize(const std::vector<Entity*>& vec) {

	int16_t minX = floor(0.0f / getTileSize().x);
	int16_t minY = floor(0.0f / getTileSize().y);

	int16_t maxX = floor(100.0f / getTileSize().x);
	int16_t maxY = floor(100.0f / getTileSize().y);

	b2Vec2 halfSize = getTileSize();
	halfSize *= 0.5f;

	for(int16_t y = minY; y < maxY; y++) {
		for(int16_t x = minX; x < maxX; x++) {
			uint32_t key = x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);

			b2Vec2 worldPos = tileToWorldCoordinates({x, y});

			ForestNode* node = new ForestNode(*this);

			for(Entity* entity : vec) {
				Obstacle* obstacle = dynamic_cast<Obstacle*>(entity);

				if(!obstacle)
					continue;

				if(obstacle->isBlocking(worldPos + halfSize, getTileSize())) {
					node->setObstructed(true);
					break;
				}
			}

			node->setPosition(x, y);

			for(int i = -1; i <= 2; i++) {

				int16_t newX = i == 2 ? x - 1 : x + i;
				int16_t newY = i == 2 ? y : y - 1;

				if(newX < minX || newX >= maxX || newY < minY || newY >= maxY)
					continue;

				uint32_t otherKey = keyOf(sf::Vector2i {newX, newY });


				ForestNode* other = map[otherKey];

				float dst = node->distanceTo(other);

				if(!other->isObstructed())
					node->addChild(other, dst);

				if(!node->isObstructed())
					other->addChild(node, dst);
			}

			map[key] = node;
		}
	}
}

void ForestPathFinder::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	int16_t minX = floor(0.0f / getTileSize().x);
	int16_t minY = floor(0.0f / getTileSize().y);

	int16_t maxX = floor(100.0f / getTileSize().x);
	int16_t maxY = floor(100.0f / getTileSize().y);

	for(int16_t y = minY; y < maxY; y++) {
		for(int16_t x = minX; x < maxX; x++) {
			uint32_t key = x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);
			if(!map.at(key)->isObstructed())
				continue;

			b2Vec2 worldPos = tileToWorldCoordinates({x, y});
			b2Vec2 center = worldPos;
			center.x += getTileSize().x / 2.0f;
			center.y += getTileSize().y / 2.0f;

			debugSprite.setPosition(sf::Vector2f(center.x, 100.0f - center.y));
			debugSprite.setOrigin({ 0.5f, 0.5f });
			debugSprite.setScale(sf::Vector2f(getTileSize().x, getTileSize().y));
			target.draw(debugSprite);
		}
	}
}

bool ForestPathFinder::findPath(b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*>& path) const {
	pathFinder.setStart(*getNode(start));

	ForestNode* processDest = getNode(goal);
	ForestNode* originalDest = processDest;

	while(processDest->isObstructed()) {
		goal.y -= getTileSize().y / 4.0f;
		processDest = getNode(goal);
	}
	pathFinder.setGoal(*processDest);

	if(pathFinder.getStart() == pathFinder.getGoal())
		return false;

	for (const auto & [key, value] : map)
		value->release();

	path.clear();
	bool found = pathFinder.findPath<pf::AStar>(path);

	if(found && processDest != originalDest)
		path.push_back(originalDest);

	pf::AStar::getInstance().clear();

	return found;
}

b2Vec2 ForestPathFinder::getTileSize() const {
	return { 2.5f, 2.5f };
}

b2Vec2 ForestPathFinder::getTileStart() const {
	return { 0.0f, 0.0f };
}

sf::Vector2i ForestPathFinder::worldToTileCoordinates(b2Vec2 worldCoords) const {
	int16_t x = static_cast<int16_t>(floor((worldCoords.x + getTileStart().x) / getTileSize().x));
	int16_t y = static_cast<int16_t>(floor((worldCoords.y + getTileStart().y) / getTileSize().y));

	return { x, y };
}

b2Vec2 ForestPathFinder::tileToWorldCoordinates(sf::Vector2i worldCoords) const {
	float x = worldCoords.x * getTileSize().x - getTileStart().x;
	float y = worldCoords.y * getTileSize().y - getTileStart().y;

	return { x, y };
}

uint32_t ForestPathFinder::keyOf(b2Vec2 position) const {
	sf::Vector2i index = worldToTileCoordinates(position);

	return keyOf(index);
}

uint32_t ForestPathFinder::keyOf(sf::Vector2i tile) const {

	int16_t x = tile.x;
	int16_t y = tile.y;

	return x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);
}

ForestNode* ForestPathFinder::getNode(b2Vec2 position) const {

	sf::Vector2i tile = worldToTileCoordinates(position);

	int16_t minX = floor(0.0f / getTileSize().x);
	int16_t minY = floor(0.0f / getTileSize().y);

	int16_t maxX = floor(100.0f / getTileSize().x);
	int16_t maxY = floor(100.0f / getTileSize().y);

	if(tile.x > maxX - 1)
		tile.x = maxX - 1;

	if(tile.y > maxY - 1)
		tile.y = maxY - 1;

	if(tile.x < minX)
		tile.x = minX;

	if(tile.y < minY)
		tile.y = minY;

	return map.at(keyOf(tile));
}

ForestPathFinder::ForestPathFinder(const wiz::AssetLoader& assets) {
	debugSprite.setTexture(*assets.get(GameAssets::WHITE_PIXEL));
}
