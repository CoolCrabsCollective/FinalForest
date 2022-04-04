//
// Created by blexander😩😩😩😩🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_OBSTACLE_H
#define LD50_CLIENT_OBSTACLE_H


#include "Physical.h"

class Obstacle : public Physical {
public:
	virtual bool isBlocking(b2Vec2 center, b2Vec2 size) = 0;
};


#endif //LD50_CLIENT_OBSTACLE_H
