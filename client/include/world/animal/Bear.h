//
// Created by blexander😩😩😩😩🤤 on 2022-04-03.
//

#ifndef LD50_CLIENT_BEAR_H
#define LD50_CLIENT_BEAR_H


#include "Animal.h"

class Bear : public Animal {
public:
	Bear(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

protected:
	void noEnemyLeft() override;
};


#endif //LD50_CLIENT_BEAR_H
