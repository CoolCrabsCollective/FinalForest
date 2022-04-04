//
// Created by william on 2022-04-02.
//

#ifndef LD50_CLIENT_ENEMYSTATE_H
#define LD50_CLIENT_ENEMYSTATE_H

class Enemy;
class Forest;

class EnemyState {
    Enemy* enemy;
public:
	EnemyState(Enemy* enemy);

    virtual void tick(float delta) = 0;

	Enemy* getEnemy();

    Forest* getForest();
};

#endif //LD50_CLIENT_ENEMYSTATE_H
