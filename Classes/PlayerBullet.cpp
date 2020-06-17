#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "MapLayer.h"

bool PlayerBullet::init() {
    if (!Bullet::init())
        return false;

    return true;
}

bool PlayerBullet::__isTankIntersection() {
    auto& enemies = MapLayer::getInstance()->getEnemies();
    for (auto enemy : enemies) {
        if (enemy->getBoundingBox().myIntersectsRect(this->getBoundingBox())) {
            enemy->disBlood();
            return true;
        }
    }

    return false;
}

bool PlayerBullet::__isBulletIntersection() {
    auto& enemies = MapLayer::getInstance()->getEnemies();
    for (auto enemy : enemies) {
        auto bullet = static_cast<EnemyBullet*>(enemy->getBullet1());
        if (this->getBoundingBox().myIntersectsRect(bullet->getBoundingBox())) {
            bullet->setBeIntersection();
            return true;
        }
    }

    return false;
}
