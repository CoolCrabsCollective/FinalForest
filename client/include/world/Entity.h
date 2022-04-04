//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_ENTITY_H
#define LD50_CLIENT_ENTITY_H


class Forest;

class Entity {
public:
	virtual ~Entity() = default;

	virtual Forest& getForest() = 0;

    int numberOfTicksAfterDeletion = 0;
};


#endif //LD50_CLIENT_ENTITY_H
