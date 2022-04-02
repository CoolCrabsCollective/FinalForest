//
// Created by Alexander Winter on 2022-04-02.
//

#ifndef LD50_CLIENT_BIGASSTREE_H
#define LD50_CLIENT_BIGASSTREE_H


#include "Tree.h"

class BigAssTree : public Tree {
public:
	BigAssTree(Forest& forest, const b2Vec2& position);

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

	b2Vec2 getSize() const override;
};


#endif //LD50_CLIENT_BIGASSTREE_H
