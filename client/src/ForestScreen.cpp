//
// Created by Alexander Winter on 2022-04-01.
//

#include "ForestScreen.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "GameAssets.h"

ForestScreen::ForestScreen(wiz::Game& game)
		: Screen(game), world(b2Vec2(0.0f, 0.0f)) {

	//b2BodyDef wallBodyDef;
	//wallBodyDef.position.Set(50.0f, 5.0f);

	//b2Body* wallBody = world.CreateBody(&wallBodyDef);

	//b2PolygonShape wallBox;

	// The extents are the half-widths of the box.
	//wallBox.SetAsBox(100.0f, 5.0f);

	// Add the ground fixture to the ground body.
	//wallBody->CreateFixture(&wallBox, 0.0f);

	for(int i = 0; i < 12; i++) {

		for(int j = 0; j < 12; j++) {
			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(i * 10.0f + float(rand()) / float((RAND_MAX)) * 6.0f - 3.0f,
								 j * 10.0f + float(rand()) / float((RAND_MAX)) * 6.0f - 3.0f);

			if(b2DistanceSquared(bodyDef.position, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f)
				continue;

			b2Body* body = world.CreateBody(&bodyDef);

			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f, 1.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.3f;

			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);
		}

	}

	sprite.setTexture(*getAssets().get(GameAssets::WHITE_PIXEL));
}

void ForestScreen::tick(float delta) {
    world.Step(delta / 1000.0f, 6, 2);
}

void ForestScreen::render(sf::RenderTarget& target) {
	target.clear();
	target.setView(sf::View({50.0f, 50.0f}, {213.33f, 120.0f}));
	b2AABB aabb, shapeAABB;
	b2Transform transform;
	for(b2Body* body = world.GetBodyList(); body != nullptr; body = body->GetNext()) {
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
    target.setView(sf::View({800.0f, 450.0f}, {1600.0f, 900.0f}));
    target.draw(nutCountText);
}

void ForestScreen::show() {
    nutCountText.setString("0");
    nutCountText.setPosition(sf::Vector2f(1550, 0));
    nutCountText.setCharacterSize(20);
    nutCountText.setFont(*getGame().getAssets().get(GameAssets::SANS_TTF));

	getGame().addWindowListener(this);
}

void ForestScreen::hide() {
	getGame().removeWindowListener(this);
}

const std::string& ForestScreen::getName() const {
	return name;
}

void ForestScreen::windowClosed() {
	getGame().getWindow().close();
}
