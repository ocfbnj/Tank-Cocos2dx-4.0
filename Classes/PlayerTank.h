#pragma once

#include "TankBase.h"


class PlayerTank : public TankBase {
public:
    bool init() override;

    void setDir(Dir d) override;
    void shoot() override;

    void setBeControl(bool b = true);
    bool isBeControl();
    void disBlood() override;

    static void loadFrameAnimation();                          // 加载坦克移动帧动画

    CREATE_FUNC(PlayerTank);

protected:
    const cocos2d::Vector<cocos2d::Animate*>* __getAnimations() override;

private:
    bool beControl = false;
    static cocos2d::Vector<cocos2d::Animate*> animations[4];   // 存储坦克移动帧动画（方向和等级）

    void __initBullets() override;
};
