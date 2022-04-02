//
// Created by cedric on 2022-04-02.
//

#include "world/Tree.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Box2D/Box2D.h"


Tree::Tree(const wiz::AssetLoader& assets) {
	sprite.setTexture(*assets.get(GameAssets::WHITE_PIXEL));
}

void Tree::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	b2AABB aabb, shapeAABB;
	b2Transform transform;

	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	for(b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext()) {
		int childCount = fixture->GetShape()->GetChildCount();
		for(int child = 0; child < childCount; child++) {
			transform = body->GetTransform();
			transform.Set(transform.p, 0.0f);
			fixture->GetShape()->ComputeAABB(&shapeAABB, transform, child);
			aabb.Combine(shapeAABB);
		}
	}
	b2Vec2 pos = aabb.GetCenter();
	b2Vec2 size = 2.0f * aabb.GetExtents();
	sprite.setPosition({pos.x, 100.0f - pos.y});
	sprite.setOrigin({0.5f, 0.5f});
	sprite.setScale({size.x, size.y});
	sprite.setRotation(sf::radians(body->GetTransform().q.GetAngle()));
	target.draw(sprite);
}
