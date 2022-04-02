//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_FORESTNODE_H
#define LD50_CLIENT_FORESTNODE_H


#include "PathFinder/AStar.h"
#include "Common/b2Math.h"

class ForestPathFinder;

class ForestNode : public pf::AStarNode {
	ForestPathFinder& pathFinder;

	bool obstructed = false;
public:
	ForestNode(ForestPathFinder& pathFinder);

	float distanceTo(AStarNode* node) const override;

	b2Vec2 getWorldPosition() const;

	bool isObstructed() const;

	void setObstructed(bool obstructed);
};


#endif //LD50_CLIENT_FORESTNODE_H
