#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "Common.h"

// 坦克等级
// 玩家分为4类
// 2级及以上可发射两枚子弹
// 敌人分为4种
using TankLevel = short;

class TankBase : public cocos2d::Sprite {
public:
    bool init() override;

    virtual void playAnimate();                         // 播放移动动画
    virtual void stopAnimate();                         // 停止播放动画
    virtual void shoot();                               // 发射子弹
    virtual void setDir(Dir d) = 0;                     // 坦克改变方向

    void startMove();                                   // 开启自动移动
    void stopMove();                                    // 停止自动移动

    cocos2d::Vector<Bullet*>& getAllBullets();          // 获得坦克拥有的所有子弹

protected:
    virtual void __initSpriteFrameCache() = 0;          // 初始化坦克精灵帧缓存
    virtual void __initBullets();                       // 创建子弹

    void __autoMove(float t);                           // 自动移动
    void __adjustPosition();                            // 调整位置为8的倍数
    void __shoot(Bullet* bullet);                       // 发射子弹辅助函数

    Dir dir;                                            // 坦克当前方向
    TankLevel level;                                    // 坦克当前等级
    cocos2d::Vector<cocos2d::Animate*> animations[4];   // 存储坦克动画（方向和等级）
    cocos2d::Vector<Bullet*> bullets;                   // 存储坦克所有的子弹

private:
    static float __adjustNumber(int number);            // 将给定数字调整为8的倍数
    bool __isMapIntersection();                         // 检测坦克与地图边缘的碰撞
    bool __isBlockIntersection();                       // 检测坦克与方块的碰撞
    bool __isTankIntersection();                        // 检测坦克之间的碰撞
};
