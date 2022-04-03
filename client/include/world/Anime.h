//
// Created by william on 2022-04-03.
//

#ifndef LD50_CLIENT_ANIME_H
#define LD50_CLIENT_ANIME_H

#include "SFML/Graphics.hpp"

class Anime {
private:
    std::vector<sf::Texture*> animationFrames;
    float msBetweenFrames = 300.0f;
    float timeSinceLastFrame = 0.0f;
    int currentFrame = 0;
    sf::Sprite* sprite;

protected:
    void insertFrame(sf::Texture* attackTexture);
    void setStateSprite(sf::Sprite* sprite);

public:
    void animate(float delta);
    void resetAnimationState();

};

#endif //LD50_CLIENT_ANIME_H
