//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#ifndef LD50_CLIENT_RENDERABLE_H
#define LD50_CLIENT_RENDERABLE_H


#include "SFML/Graphics/Drawable.hpp"

class Renderable : public sf::Drawable {
public:
	virtual float getZOrder() const = 0;
};


#endif //LD50_CLIENT_RENDERABLE_H
