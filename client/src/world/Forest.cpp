//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/Forest.h"
#include "world/Entity.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include "world/Tree.h"
#include "world/Squirrel.h"

Forest::Forest(const wiz::AssetLoader& assetLoader) : assetLoader(assetLoader), world(b2Vec2_zero) {
	for(int i = 0; i < 12; i++) {
		for(int j = 0; j < 12; j++) {
			b2Vec2 position(i * 10.0f + float(rand()) / float((RAND_MAX)) * 6.0f - 3.0f,
							j * 10.0f + float(rand()) / float((RAND_MAX)) * 6.0f - 3.0f);

			if(b2DistanceSquared(position, b2Vec2(50.0f, 50.0f)) > 50.0f * 50.0f)
				continue;
			objects.push_back(new Tree(*this, position));
		}
	}


	objects.push_back(new Squirrel(*this, b2Vec2(0.0f, 0.0f)));
}

Forest::~Forest() {
	for(Entity* entity : objects)
		delete entity;
	objects.clear();
}

void Forest::tick(float delta) {
	for(Entity* obj : objects) {
		Tickable* tickable = dynamic_cast<Tickable*>(obj);
		if(tickable)
			tickable->tick(delta);
	}

	world.Step(delta / 1000.0f, 6, 2);
}

void Forest::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {

	for(Entity* obj : objects) {
		sf::Drawable* drawable = dynamic_cast<sf::Drawable*>(obj);
		if(drawable)
			target.draw(*drawable, states);
	}
}

b2World& Forest::getB2World() {
	return world;
}

const wiz::AssetLoader& Forest::getAssets() const {
	return assetLoader;
}
