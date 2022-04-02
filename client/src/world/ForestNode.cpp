//
// Created by Alexander Winter on 2022-04-02.
//

#include "world/ForestNode.h"
#include <cmath>

float ForestNode::distanceTo(pf::AStarNode* node) const {
	float diffX = static_cast<float>(node->getX() - getX());
	float diffY = static_cast<float>(node->getY() - getY());
	return std::sqrt(diffX * diffX + diffY * diffY);
}
