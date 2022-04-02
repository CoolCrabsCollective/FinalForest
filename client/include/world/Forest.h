//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FOREST_H
#define LD50_CLIENT_FOREST_H


#include "Tickable.h"
#include "SFML/Graphics/Drawable.hpp"

class Forest : public sf::Drawable, public Tickable {
protected:
	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
};


#endif //LD50_CLIENT_FOREST_H
