//
// Created by william on 2022-04-04.
//

#ifndef LD50_CLIENT_ANIME_H
#define LD50_CLIENT_ANIME_H

#include "SFML/Graphics.hpp"

class Anime {
private:
    std::vector<sf::Texture*> frames;
    float msBetweenFrames = 500.0f;
    float timeSinceLastFrame = 0;
    int currentFrame = 0;

    bool isAnimating = false;

    sf::Sprite* sprite;

protected:
    void insertFrame(sf::Texture* attackTexture);
    void setStateSprite(sf::Sprite* sprite);
    void tickAnimation();

public:
    void startAnimation();
    void runAnimation(float delta);
    void resetAnimation();
};

#endif //LD50_CLIENT_ANIME_H
