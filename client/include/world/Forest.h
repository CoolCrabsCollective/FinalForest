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

class Forest : public sf::Drawable, public Tickable {
	const wiz::AssetLoader& assetLoader;
	b2World world;

	std::vector<Entity*> objects;
public:
    int nutCount;

	Forest(const wiz::AssetLoader& assetLoader);

	~Forest() override;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2World& getB2World();

	const wiz::AssetLoader& getAssets() const;

	void tick(float delta) override;
};


#endif //LD50_CLIENT_FOREST_H
