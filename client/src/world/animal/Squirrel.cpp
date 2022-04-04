//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/state/SquirrelIdleState.h"

#include <memory>
#include "world/state/SquirrelGatherState.h"
#include "world/state/SquirrelReturnGatherState.h"
#include "world/state/SquirrelGoAttackState.h"
#include "world/animal/Squirrel.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "Box2D/Box2D.h"
#include "ForestScreen.h"
#include "world/state/SquirrelAttackState.h"

Squirrel::Squirrel(Forest& forest, b2Vec2 position) : Animal(forest, position) {
    setPower(1.0);

    squirrelWalk = forest.getAssets().get(GameAssets::SQUIRREL);
    squirrelIdle = forest.getAssets().get(GameAssets::SQUIRREL_IDLE);
    squirrelNut = forest.getAssets().get(GameAssets::SQUIRREL_WITH_NUT);
    squirrelAttack = forest.getAssets().get(GameAssets::SQUIRREL_ARMORED);
	sprite.setTexture(*squirrelWalk);

	this->state = std::make_shared<SquirrelIdleState>(&this->forest, this);
    // Update the squirrel count.
    forest.squirrelCount++;
}


void Squirrel::tick(float delta) {

    if(dynamic_pointer_cast<SquirrelIdleState>(state).get() || dynamic_pointer_cast<SquirrelGatherState>(state).get())
        sprite.setTexture(*squirrelIdle);
    else if(dynamic_pointer_cast<SquirrelReturnGatherState>(state).get())
        sprite.setTexture(*squirrelNut);
    else if(dynamic_pointer_cast<SquirrelGoAttackState>(state).get() ||
            dynamic_pointer_cast<SquirrelAttackState>(state).get())
        sprite.setTexture(*squirrelAttack);
    else
        sprite.setTexture(*squirrelWalk);

	Animal::tick(delta);
}

b2Vec2 Squirrel::getSize() const {
	return {1.5f, 1.5f};
}

std::shared_ptr<SquirrelState> Squirrel::getState() const {
    return state;
}

void Squirrel::setState(std::shared_ptr<SquirrelState> state) {
    Squirrel::state = state;
}

void Squirrel::targetNearestEnemy() {
    if (forest.getEnemies().size() <= 1)
        return;

    std::vector enemies(forest.getEnemies());

    if (enemies.size() > 2) {
        std::sort(enemies.begin(), enemies.end() - 1, [this](Enemy* a, Enemy* b){
            float a_dis = b2DistanceSquared(a->getPosition(), body->GetPosition());
            float b_dis = b2DistanceSquared(b->getPosition(), body->GetPosition());
            return a_dis < b_dis;
        });
    }

    for (Enemy* enemy : enemies) {
        if (!enemy->isDestroyed()) {
            this->state = std::make_shared<SquirrelGoAttackState>(&this->forest, this, enemy);
            break;
        }
    }
}
