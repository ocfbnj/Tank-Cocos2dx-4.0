#pragma once

#include "cocos2d.h"
#include "Common.h"

using BulletLevel = short;

class Bullet : public cocos2d::Sprite {
public:
    bool init() override;

    void startMove();

    void setDir(Dir d);
    void setLevel(BulletLevel lev);

    static void addSpriteFrameCache();

private:
    void __autoMove(float t);
    void __stopMove();
    bool __isMapIntersection();                     // 检测和地图边缘的碰撞
    bool __isBlockIntersection();                   // 检测和方块的碰撞
    virtual bool __isTankIntersection() = 0;        // 检测和坦克的碰撞
    virtual bool __isBulletIntersection() = 0;      // 检测和子弹的碰撞
    void __showEffect();                            // 展示碰撞特效

    Dir dir{};                                      // 子弹方向
    BulletLevel level{};                            // 子弹等级
};
