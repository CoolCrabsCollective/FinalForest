//
// Created by Alexander Winter🤤 on 2022-04-02.
//

#include "world/pathfinding/ForestNode.h"
#include "world/Forest.h"
#include "world/pathfinding/ForestPathFinder.h"


ForestNode::ForestNode(ForestPathFinder& pathFinder, b2Vec2 worldPos)
	: pathFinder(pathFinder), worldPos(worldPos)
{

}

float ForestNode::distanceTo(pf::AStarNode* node) const {
	ForestNode* forestNode = dynamic_cast<ForestNode*>(node);

	if(!forestNode)
		throw std::runtime_error("Not a ForestNode");

	return b2Distance(forestNode->getWorldPosition(), getWorldPosition());
}

b2Vec2 ForestNode::getWorldPosition() const {
	return worldPos;
}

bool ForestNode::isObstructed() const {
	return obstructed;
}

void ForestNode::setObstructed(bool obstructed) {
	ForestNode::obstructed = obstructed;
}
