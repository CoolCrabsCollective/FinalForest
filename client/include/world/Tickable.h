//
// Created by blexander😩😩😩😩🤤 on 2022-04-02.
//

#ifndef LD50_CLIENT_TICKABLE_H
#define LD50_CLIENT_TICKABLE_H


class Tickable {
public:
	virtual ~Tickable() = default;

	virtual void tick(float delta) = 0;
};


#endif //LD50_CLIENT_TICKABLE_H
