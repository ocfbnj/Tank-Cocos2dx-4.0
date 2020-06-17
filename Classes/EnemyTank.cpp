#include "Common.h"

#include "EnemyTank.h"

USING_NS_CC;

cocos2d::Vector<cocos2d::Animate*> EnemyTank::animations[4]{};

bool EnemyTank::init() {
    if (!TankBase::init()) {
        return false;
    }

    // TODO: 删掉这行
    level = 3;

    // 展示出生动画
    birthAnimation("enemy_" + std::to_string(int(dir)) + "_" + std::to_string(level));

    return true;
}

void EnemyTank::setDir(Dir d) {}

void EnemyTank::loadFrameAnimation() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

    // 总共4个等级
    for (int i = 0; i < 4; i++) {
        std::string lev = std::to_string(i);
        // 总共4个方向
        for (int j = 0; j < 4; j++) {
            std::string d = std::to_string(j);
            auto enemy_1 = SpriteFrame::create("images/enemy_tank/normal_tank/" + std::to_string(i + 1) + "-" + std::to_string(j + 1) + "-1.png", tankRect);
            auto enemy_2 = SpriteFrame::create("images/enemy_tank/normal_tank/" + std::to_string(i + 1) + "-" + std::to_string(j + 1) + "-2.png", tankRect);
            auto enemy = Animation::createWithSpriteFrames({ enemy_1, enemy_2 }, 0.05f);

            enemy_1->getTexture()->setAliasTexParameters();
            enemy_2->getTexture()->setAliasTexParameters();

            // 添加到缓存
            spriteFrameCache->addSpriteFrame(enemy_1, "enemy_" + d + "_" + lev);

            // 保存
            animations[j].pushBack(Animate::create(enemy));
        }
    }
}

const cocos2d::Vector<cocos2d::Animate*>* EnemyTank::__getAnimations() {
    return animations;
}
