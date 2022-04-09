//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#include <unordered_map>
#include "world/Physical.h"
#include "world/pathfinding/ForestPathFinder.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Obstacle.h"
#include "world/water/River.h"
#include "world/tree/Tree.h"
#include "world/tree/BigAssTree.h"


ForestPathFinder::ForestPathFinder(const wiz::Logger& logger, const wiz::AssetLoader& assets)
	: logger(logger)
{
	debugSprite.setTexture(*assets.get(GameAssets::WHITE_PIXEL));
}

void ForestPathFinder::initialize(const std::vector<Entity*>& vec) {

	int16_t minX = 0;
	int16_t minY = 0;

	int16_t maxX = floor((getTileEnd().x - getTileStart().x) / getTileSize().x);
	int16_t maxY = floor((getTileEnd().y - getTileStart().y) / getTileSize().y);

	b2Vec2 halfSize = getTileSize();
	halfSize *= 0.5f;

	for(int16_t y = minY; y < maxY; y++) {
		for(int16_t x = minX; x < maxX; x++) {
			uint32_t key = x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);

			b2Vec2 worldPos = tileToWorldCoordinates({x, y}) + halfSize;

			ForestNode* animalNode = new ForestNode(*this, worldPos);
			ForestNode* enemyNode = new ForestNode(*this, worldPos);

			animalNode->setPosition(x, y);
			enemyNode->setPosition(x, y);

			for(Entity* entity : vec) {
				Obstacle* obstacle = dynamic_cast<Obstacle*>(entity);

				if(!obstacle || dynamic_cast<Tree*>(entity) && !dynamic_cast<BigAssTree*>(entity))
					continue;

				if(obstacle->isBlocking(worldPos, getTileSize())) {
					if(dynamic_cast<River*>(entity)) {
						enemyNode->setObstructed(true);
					} else {
						animalNode->setObstructed(true);
						enemyNode->setObstructed(true);
						break;
					}
				}
			}

			for(int i = -1; i <= 2; i++) {

				int16_t newX = i == 2 ? x - 1 : x + i;
				int16_t newY = i == 2 ? y : y - 1;

				if(newX < minX || newX >= maxX || newY < minY || newY >= maxY)
					continue;

				uint32_t otherKey = keyOf(sf::Vector2i {newX, newY });

				ForestNode* otherAnimalNode = animalMap[otherKey];
				ForestNode* otherEnemyNode = enemyMap[otherKey];

				float dst = animalNode->distanceTo(otherAnimalNode);

				if(!otherAnimalNode->isObstructed())
					animalNode->addChild(otherAnimalNode, dst);

				if(!animalNode->isObstructed())
					otherAnimalNode->addChild(animalNode, dst);


				if(!otherEnemyNode->isObstructed())
					enemyNode->addChild(otherEnemyNode, dst);

				if(!enemyNode->isObstructed())
					otherEnemyNode->addChild(enemyNode, dst);
			}

			animalMap[key] = animalNode;
			enemyMap[key] = enemyNode;
		}
	}
}

void ForestPathFinder::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	int16_t minX = 0;
	int16_t minY = 0;

	int16_t maxX = floor((getTileEnd().x - getTileStart().x) / getTileSize().x);
	int16_t maxY = floor((getTileEnd().y - getTileStart().y) / getTileSize().y);

	for(int16_t y = minY; y < maxY; y++) {
		for(int16_t x = minX; x < maxX; x++) {
			uint32_t key = x & 0x0000FFFF | (static_cast<uint32_t>(y << 16) & 0xFFFF0000);
			if(!animalMap.at(key)->isObstructed() && !enemyMap.at(key)->isObstructed())
				continue;

			b2Vec2 worldPos = tileToWorldCoordinates({x, y});
			b2Vec2 center = worldPos;
			center.x += getTileSize().x / 2.0f;
			center.y += getTileSize().y / 2.0f;

			debugSprite.setPosition(sf::Vector2f(center.x, 100.0f - center.y));
			debugSprite.setOrigin({ 0.5f, 0.5f });
			debugSprite.setScale(sf::Vector2f(getTileSize().x, getTileSize().y));
			debugSprite.setColor(animalMap.at(key)->isObstructed() ? sf::Color::White : sf::Color::Green);
			target.draw(debugSprite);
		}
	}
}

bool ForestPathFinder::findPath(PathType pathType, b2Vec2 start, b2Vec2 goal, std::vector<ForestNode*>& path) const {
	pathFinder.setStart(pathType == ANIMAL_UNIT ? *animalNode(start) : *enemyNode(start));

	ForestNode* processDest = pathType == ANIMAL_UNIT ? animalNode(goal) : enemyNode(goal);
	ForestNode* originalDest = processDest;

	while(processDest->isObstructed()) {
		goal.y -= getTileSize().y / 4.0f;
		processDest = pathType == ANIMAL_UNIT ? animalNode(goal) : enemyNode(goal);
	}
	pathFinder.setGoal(*processDest);

	if(pathFinder.getStart() == pathFinder.getGoal())
		return false;

	for (const auto & [key, value] : pathType == ANIMAL_UNIT ? animalMap : enemyMap)
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
	return { -60.0f, -60.0f };
}

b2Vec2 ForestPathFinder::getTileEnd() const {
	return { 160.0f, 160.0f };
}

sf::Vector2i ForestPathFinder::worldToTileCoordinates(b2Vec2 worldCoords) const {
	int16_t x = static_cast<int16_t>(floor((worldCoords.x - getTileStart().x) / getTileSize().x));
	int16_t y = static_cast<int16_t>(floor((worldCoords.y - getTileStart().y) / getTileSize().y));

	return { x, y };
}

b2Vec2 ForestPathFinder::tileToWorldCoordinates(sf::Vector2i worldCoords) const {
	float x = worldCoords.x * getTileSize().x + getTileStart().x;
	float y = worldCoords.y * getTileSize().y + getTileStart().y;

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

ForestNode* ForestPathFinder::animalNode(b2Vec2 position) const {

	sf::Vector2i tile = worldToTileCoordinates(position);

	int16_t minX = 0;
	int16_t minY = 0;

	int16_t maxX = floor((getTileEnd().x - getTileStart().x) / getTileSize().x);
	int16_t maxY = floor((getTileEnd().y - getTileStart().y) / getTileSize().y);

	if(tile.x > maxX - 1)
		tile.x = maxX - 1;

	if(tile.y > maxY - 1)
		tile.y = maxY - 1;

	if(tile.x < minX)
		tile.x = minX;

	if(tile.y < minY)
		tile.y = minY;

	return animalMap.at(keyOf(tile));
}

ForestNode* ForestPathFinder::enemyNode(b2Vec2 position) const {

	sf::Vector2i tile = worldToTileCoordinates(position);

	int16_t minX = 0;
	int16_t minY = 0;

	int16_t maxX = floor((getTileEnd().x - getTileStart().x) / getTileSize().x);
	int16_t maxY = floor((getTileEnd().y - getTileStart().y) / getTileSize().y);

	if(tile.x > maxX - 1)
		tile.x = maxX - 1;

	if(tile.y > maxY - 1)
		tile.y = maxY - 1;

	if(tile.x < minX)
		tile.x = minX;

	if(tile.y < minY)
		tile.y = minY;

	return enemyMap.at(keyOf(tile));
}

void ForestPathFinder::addBridge(b2Vec2 start, b2Vec2 end) {

	int16_t minX = 0;
	int16_t minY = 0;

	int16_t maxX = floor((getTileEnd().x - getTileStart().x) / getTileSize().x);
	int16_t maxY = floor((getTileEnd().y - getTileStart().y) / getTileSize().y);

	sf::Vector2i startIndex = worldToTileCoordinates(start);
	sf::Vector2i endIndex = worldToTileCoordinates(end);

	ForestNode* startNode = new ForestNode(*this, start);
	startNode->setPosition(startIndex.x, startIndex.y);
	startNode->setObstructed(false);

	ForestNode* endNode = new ForestNode(*this, end);
	endNode->setPosition(endIndex.x, endIndex.y);
	endNode->setObstructed(false);

	float dst = b2Distance(start, end);

	startNode->addChild(endNode, dst);
	endNode->addChild(startNode, dst);

	for(int16_t i = -1; i <= 1; i++) {
		for(int16_t j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;

			int16_t startNBX = startIndex.x + i;
			int16_t startNBY = startIndex.y + j;

			if(startNBX < minX || startNBX >= maxX || startNBY < minY || startNBY >= maxY)
				continue;

			uint32_t otherKey = keyOf(sf::Vector2i {startNBX, startNBY });

			ForestNode* otherEnemyNode = enemyMap[otherKey];

			if(otherEnemyNode == nullptr) {
				logger.error("Other enemy node null in addBridge");
				return;
			}

			float dst = b2Distance(otherEnemyNode->getWorldPosition(), start);

			if(!otherEnemyNode->isObstructed())
				startNode->addChild(otherEnemyNode, dst);

			otherEnemyNode->addChild(startNode, dst);
		}
	}

	for(int16_t i = -1; i <= 1; i++) {
		for(int16_t j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;

			int16_t endNBX = endIndex.x + i;
			int16_t endNBY = endIndex.y + j;

			if(endNBX < minX || endNBX >= maxX || endNBY < minY || endNBY >= maxY)
				continue;

			uint32_t otherKey = keyOf(sf::Vector2i {endNBX, endNBY });

			ForestNode* otherEnemyNode = enemyMap[otherKey];

			if(otherEnemyNode == nullptr) {
				logger.error("Other enemy node null in addBridge");
				return;
			}

			float dst = b2Distance(otherEnemyNode->getWorldPosition(), end);

			if(!otherEnemyNode->isObstructed())
				endNode->addChild(otherEnemyNode, dst);

			otherEnemyNode->addChild(endNode, dst);
		}
	}
}
