//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FORESTNODE_H
#define LD50_CLIENT_FORESTNODE_H


#include "PathFinder/AStar.h"

class ForestNode : public pf::AStarNode {
public:
	bool obstructed = false;
	float distanceTo(AStarNode* node) const override;
};


#endif //LD50_CLIENT_FORESTNODE_H
