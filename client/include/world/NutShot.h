//
// Created by cedric on 2022-04-03.
//

#ifndef LD50_COMMON_NUTSHOT_H
#define LD50_COMMON_NUTSHOT_H

#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/Drawable.hpp"
#include "Tickable.h"
class NutShot : public sf::Drawable, public Tickable {
    private:
        sf::Vector2f pos;
        sf::Vector2f target;
        float speed;
        float damage;

};


#endif //LD50_COMMON_NUTSHOT_H
