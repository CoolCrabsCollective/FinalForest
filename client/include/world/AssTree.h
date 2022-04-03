//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_BIGASSTREE_H
#define LD50_CLIENT_BIGASSTREE_H

#include "Tree.h"

class AssTree : public Tree {
public:
	AssTree(Forest& forest, const b2Vec2& position);

	b2Vec2 getSize() const override;
};


#endif //LD50_CLIENT_BIGASSTREE_H
