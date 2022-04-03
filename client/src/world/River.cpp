//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/River.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Collision/Shapes/b2PolygonShape.h"
#include "Dynamics/b2Fixture.h"
#include "ForestScreen.h"
#include "util/math_util.h"

River::River(Forest& forest, std::vector<b2Vec2> path, float width) : forest(forest), path(path), width(width) {
	sf::Texture* tex = forest.getAssets().get(GameAssets::RIVER_LINE);
	tex->setRepeated(true);
	river_line.setTexture(*tex);
	river_joint.setTexture(*forest.getAssets().get(GameAssets::RIVER_JOINT));

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;

	b2Vec2 base = path[0];
	bodyDef.position.Set(base.x, base.y);

	body = forest.getB2World().CreateBody(&bodyDef);

	b2Vec2 prev = base;
	for(size_t i = 1; i < path.size(); i++) {
		float dst = b2Distance(prev, path[i]);
		b2Vec2 center = (prev + path[i]);
		center *= 0.5f;
		center -= base;

		b2Vec2 dir = path[i] - prev;
		sf::Vector2f vec = { dir.x, dir.y };

		b2PolygonShape rect;
		rect.SetAsBox(dst / 2.0f, width / 2.0f, center, vec.angle().asRadians());

		// Add the shape to the body.
		body->CreateFixture(&rect, 0.0f);
		prev = path[i];
	}
}

void River::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	b2Vec2 prev = path[0];

	river_joint.setPosition(sf::Vector2f(path[0].x, 100.0f - path[0].y));
	river_joint.setOrigin({ 0.5f * river_line.getTexture()->getSize().x, 0.5f * river_line.getTexture()->getSize().y });
	river_joint.setScale(sf::Vector2f(width / river_line.getTexture()->getSize().x, width / river_line.getTexture()->getSize().y));
	river_joint.setRotation(sf::degrees(0.0f));
	target.draw(river_joint);

	for(size_t i = 1; i < path.size(); i++) {
		float dst = b2Distance(prev, path[i]);
		b2Vec2 center = (prev + path[i]);
		center *= 0.5f;

		b2Vec2 dir = path[i] - prev;
		sf::Vector2f vec = { dir.x, -dir.y };

		river_joint.setPosition(sf::Vector2f(path[i].x, 100.0f - path[i].y));
		river_joint.setOrigin({ 0.5f * river_joint.getTexture()->getSize().x, 0.5f * river_joint.getTexture()->getSize().y });
		river_joint.setScale(sf::Vector2f(width / river_joint.getTexture()->getSize().x, width / river_joint.getTexture()->getSize().y));
		river_joint.setRotation(vec.angle());
		target.draw(river_joint);

		river_line.setPosition(sf::Vector2f(prev.x, 100.0f - prev.y));
		river_line.setOrigin({ 0.0f, 0.5f * river_line.getTexture()->getSize().y });
		river_line.setScale(sf::Vector2f(width * 3.0f / river_line.getTexture()->getSize().x,
										 width / river_line.getTexture()->getSize().y));
		river_line.setRotation(vec.angle());
		river_line.setTextureRect(sf::IntRect({0, 0},
											  {(int)round(dst / width * 8.0f), 8}));
		target.draw(river_line);

		prev = path[i];
	}
}

b2Body* River::getBody() const {
	return body;
}

b2Vec2 River::getPosition() const {
	return body->GetPosition();
}

b2Vec2 River::getSize() const {
	return b2Vec2(10.0f, 10.0f);
}

Forest& River::getForest() const {
	return forest;
}

bool River::isBlocking(b2Vec2 center, b2Vec2 size) {
	b2Vec2 halfSize = size;
	halfSize *= 0.5f;

	b2Vec2 prev = path[0];
	for(size_t i = 1; i < path.size(); i++) {
		float dst = b2Distance(prev, path[i]);
		b2Vec2 riverCenter = (prev + path[i]);
		riverCenter *= 0.5f;

		b2Vec2 dir = path[i] - prev;
		sf::Vector2f vec = { dir.x, -dir.y };

		if(doOBBCollideWithOBB(center.x, center.y, size.x, size.y, 0.0f,
							   riverCenter.x, riverCenter.y, dst, width, vec.angle().asDegrees()))
			return true;

		prev = path[i];
	}

	return false;
}
