//
// Created by William Wells on 2022-04-02.
//

#include "world/Forest.h"
#include "world/enemy/LumberJackChainsaw.h"
#include "GameAssets.h"
#include "SFML/Graphics/RenderTarget.hpp"

LumberJackChainsaw::LumberJackChainsaw(Forest& forest, const b2Vec2& position)
	: LumberJack(forest, position)
{
    setSpeed(15.0f);
    setPower(1.0);
    setStateSprite(&sprite);
    insertAttackFrame(forest.getAssets().get(GameAssets::LUMBERJACKCHAINSAW));
    insertAttackFrame(forest.getAssets().get(GameAssets::LUMBERJACKCHAINSAW_SWING));
	sprite.setTexture(*forest.getAssets().get(GameAssets::LUMBERJACKCHAINSAW), true);
    setHealth(8.f);
}
