//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#include "world/water/Bridge.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "world/water/River.h"

Bridge::Bridge(const River& river, int segmentIndex, BridgeType type)
	: river(river), segmentIndex(segmentIndex), bridgeType(type)
{
	sprite.setTexture(*river.getForest().getAssets().get(type == WOOD
			? GameAssets::WOOD_BRIDGE
			: GameAssets::METAL_BRIDGE));

	position = river.getPath().at(segmentIndex) + river.getPath().at(segmentIndex + 1);
	position *= 0.5f;

	b2Vec2 diff = river.getPath().at(segmentIndex) - river.getPath().at(segmentIndex + 1);

	sf::Vector2f vec = { diff.x, -diff.y };

	angle = vec.angle().asDegrees() + 90;
}

void Bridge::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sprite.setPosition({position.x, 100.0f - position.y});
	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({6.0f / sprite.getTexture()->getSize().x, 6.0f / sprite.getTexture()->getSize().y});
	sprite.setRotation(sf::degrees(angle));
	target.draw(sprite);
}

const River& Bridge::getRiver() const {
	return river;
}

const int Bridge::getSegmentIndex() const {
	return segmentIndex;
}

const BridgeType Bridge::getBridgeType() const {
	return bridgeType;
}
