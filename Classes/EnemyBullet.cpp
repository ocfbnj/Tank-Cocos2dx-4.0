#include "EnemyBullet.h"
#include "MapLayer.h"

bool EnemyBullet::init() {
    if (!Bullet::init())
        return false;

    return true;
}

void EnemyBullet::setBeIntersection() {
    isBeIntersection = true;
}

bool EnemyBullet::__isTankIntersection() {
    auto player1 = MapLayer::getInstance()->getPlayer1();
    if (player1 && this->getBoundingBox().myIntersectsRect(player1->getBoundingBox())) {
        player1->disBlood();
        return true;
    }

    return false;
}

bool EnemyBullet::__isBulletIntersection() {
    if (isBeIntersection) {
        isBeIntersection = false;
        return true;
    }

    return false;
}
