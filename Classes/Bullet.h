#pragma once

#include "cocos2d.h"
#include "Common.h"

class Bullet : public cocos2d::Sprite {
public:
	bool init() override;

	void startMove();

	void setDir(Dir d);

	CREATE_FUNC(Bullet);

private:
	void __autoMove(float t);
	void __stopMove();
	bool __isMapIntersection();
	bool __isBlockIntersection();
	bool __isTankIntersection();
	void __showEffect();                // 展示碰撞特效

	Dir dir;
};
