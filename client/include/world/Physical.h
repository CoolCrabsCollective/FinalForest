//
// Created by blexander😩😩😩😩🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_PHYSICAL_H
#define LD50_CLIENT_PHYSICAL_H


#include "Box2D/Dynamics/b2Body.h"
#include "Entity.h"

class Physical : public Entity {
public:
	virtual ~Physical() = default;

	virtual b2Body* getBody() const = 0;

	virtual b2Vec2 getPosition() const = 0;

	virtual b2Vec2 getSize() const = 0;
};


#endif //LD50_CLIENT_PHYSICAL_H
