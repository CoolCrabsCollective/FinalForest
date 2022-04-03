//
// Created by cedric on 2022-04-03.
//

#ifndef LD50_COMMON_NUTSHOT_H
#define LD50_COMMON_NUTSHOT_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "Tickable.h"
#include "Damageable.h"
#include "Enemy.h"
#include "Forest.h"

class NutShot : public Renderable, public Tickable, public Damager, public Entity{
public:
    NutShot(Forest& forest, sf::Vector2f pos, Enemy* target);
    void tick(float delta) override;

    Forest &getForest() const override;

    float getZOrder() const override;

protected:
    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

private:
        mutable sf::Sprite sprite;
        sf::Vector2f pos;
        Enemy* target;
        float speed;
        float damage;
        Forest& forest;

};


#endif //LD50_COMMON_NUTSHOT_H
