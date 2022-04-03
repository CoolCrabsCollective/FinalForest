//
// Created by Alexander Winter on 2022-04-03.
//

#include "world/state/LumberJackLeaveState.h"
#include "ForestScreen.h"

LumberJackLeaveState::LumberJackLeaveState(Forest* forest, LumberJack* lumberJack)
		: LumberJackState(forest, lumberJack) {
	b2Vec2 newPos = lumberJack->getPosition() - b2Vec2(50.0f, 50.0f);
	newPos.Normalize();
	newPos *= 200.0f;
	newPos += lumberJack->getPosition();

	lumberJack->setDestination(newPos);
}

void LumberJackLeaveState::tick(float delta) {
	if(b2DistanceSquared(getLumberJack()->getPosition(), b2Vec2(50.0f, 50.0f)) > 100.0f * 100.0f)
	{
		getForest()->sendToCompost(getLumberJack());
		getForest()->getScreen().getLogger().debug("LumberJack is gone");
	}
}
