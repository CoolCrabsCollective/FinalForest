//
// Created by Alexander Winter🤤 on 2022-04-03.
//

#ifndef LD50_CLIENT_WOLF_H
#define LD50_CLIENT_WOLF_H

#include "Animal.h"

class Wolf : public Animal {

public:
	Wolf(Forest& forest, b2Vec2 position);

	b2Vec2 getSize() const override;

protected:
	void noEnemyLeft() override;
};


#endif //LD50_CLIENT_WOLF_H
