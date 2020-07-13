#pragma once

#include "TankBase.h"

class EnemyTank : public TankBase {
public:
    CREATE_FUNC(EnemyTank);

    bool init() override;

    void setDir(Dir d) override;

    static void loadFrameAnimation();                          // 加载坦克移动帧动画
    void changeDirection();                                    // 更改方向
    virtual void disBlood();                                   // 坦克掉血

protected:
    void __initBullets() override;
    const cocos2d::Vector<cocos2d::Animate*>*
        __getAnimations() override;

private:
    static cocos2d::Vector<cocos2d::Animate*> animations[4];   // 存储坦克移动帧动画（方向和等级）
    bool canChangeDir = false;                                 // 能否更改方向

    bool __isTankIntersection() override;
};
