//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#ifndef LD50_CLIENT_BRIDGE_H
#define LD50_CLIENT_BRIDGE_H


#include "SFML/Graphics/Drawable.hpp"
#include "Box2D/Common/b2Math.h"
#include "SFML/Graphics/Sprite.hpp"

class River;

enum BridgeType {
	WOOD,
	METAL
};

class Bridge : public sf::Drawable {
	mutable sf::Sprite sprite;

	b2Vec2 position;
	float angle;

	const River& river;
	const int segmentIndex;
	const BridgeType bridgeType;

public:
	Bridge(const River& river, int segmentIndex, BridgeType type);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	const River& getRiver() const;

	const int getSegmentIndex() const;

	const BridgeType getBridgeType() const;
};


#endif //LD50_CLIENT_BRIDGE_H
