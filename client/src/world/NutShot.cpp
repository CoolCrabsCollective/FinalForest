//
// Created by Cedric on 2022-04-03.
//

#include <GameAssets.h>
#include "world/NutShot.h"
#include "world/Forest.h"

NutShot::NutShot(Forest& forest, sf::Vector2f pos, Enemy* target) : pos(pos), target(target), forest(forest) {
    sprite.setTexture(*forest.getAssets().get(GameAssets::NUT));
    this->speed = 100;
    this->setPower(0.4f);
}

void NutShot::tick(float delta) {

    auto enemy_it = std::find(getForest().getEnemies().begin(), getForest().getEnemies().end(), this->target);
    if(enemy_it == getForest().getEnemies().end())
    {
        this->getForest().sendToCompost(this);
        return;
    }
    float diffX = this->target->getPosition().x - this->pos.x;
    float diffY = this->target->getPosition().y - this->pos.y;
    if((diffX*diffX + diffY*diffY) < 50)
    {
        this->attack(this->target);
        this->getForest().sendToCompost(this);
        return;
    }

    sf::Vector2f direction = {diffX, diffY };
    direction = direction.normalized();
    this->pos.x += direction.x * speed * delta / 1000.f;
    this->pos.y += direction.y * speed * delta / 1000.f;
}

float NutShot::getZOrder() const {
    return pos.y;
}

void NutShot::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    sprite.setPosition({pos.x, 100.0f - pos.y});
    sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});

    sprite.setScale({2.f / sprite.getTexture()->getSize().x,
                     2.f / sprite.getTexture()->getSize().y});
    sprite.rotate(sf::degrees(7.f));
    target.draw(sprite);
}

Forest &NutShot::getForest() {
    return forest;
}
