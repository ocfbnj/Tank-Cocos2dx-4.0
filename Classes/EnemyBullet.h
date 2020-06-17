#pragma once

#include "Bullet.h"

class EnemyBullet : public Bullet {
public:
    bool init() override;

    CREATE_FUNC(EnemyBullet);
    void setBeIntersection();

private:
    bool __isTankIntersection() override;
    bool __isBulletIntersection() override;

    bool isBeIntersection = false;
};