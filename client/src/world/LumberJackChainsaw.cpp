//
// Created by William Wells on 2022-04-02.
//

#include "world/Forest.h"
#include "world/LumberJackChainsaw.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

LumberJackChainsaw::LumberJackChainsaw(Forest& forest, const b2Vec2& position)
	: LumberJack(forest, position)
{
    setSpeed(15.0f);
	sprite.setTexture(*forest.getAssets().get(GameAssets::LUMBERJACKCHAINSAW), true);
}
