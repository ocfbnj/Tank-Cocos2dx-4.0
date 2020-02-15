#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "Common.h"

enum class TankLevel {
	_1_, _2_, _3_, _4_
};

class TankBase : public cocos2d::Sprite {
public:
	bool init() override;

	virtual void playAnimate();
	virtual void stopAnimate();

	virtual void setDir(Dir d) = 0;

	void moveLeft();
	void moveUp();
	void moveRight();
	void moveDown();

	void startMove();
	void stopMove();

	void shoot();

	cocos2d::Vector<Bullet*>& getAllBullets();

protected:
	virtual void __initSpriteFrameCache() = 0;

	void __initBullets();
	void __autoMove(float t);
	void __adjustPosition();

	Dir dir;
	cocos2d::Vector<cocos2d::Animate*> animations;
	cocos2d::Vector<Bullet*> bullets;

private:
	int __adjustNumber(int number);
	bool __isMapIntersection();
	bool __isBlockIntersection();
	bool __isTankIntersection();
};
