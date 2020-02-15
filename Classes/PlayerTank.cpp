#include "Common.h"

#include "PlayerTank.h"
#include "TankBase.h"

#include "cocos2d.h"

USING_NS_CC;

bool PlayerTank::init() {
	if (!TankBase::init()) {
		return false;
	}

	dir = Dir::UP;
    level = 3;
    this->initWithSpriteFrameName("player1_1_" + std::to_string(level));

	return true;
}

void PlayerTank::setDir(Dir d) {
	if (d == dir) {
		return;
	}

	dir = d;

	// 当改变方向时，将坐标调整为最接近于8的倍数
	__adjustPosition();

	std::string name = "player1_" + std::to_string((int)dir) +"_"
	        + std::to_string(level);

    // 更换图片
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

void PlayerTank::__initSpriteFrameCache() {
	auto spriteFrameCache = SpriteFrameCache::getInstance();
	Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

	// 总共4个等级
	for (int i = 0; i < 4; i++) {
	    std::string lev = std::to_string(i);

	    // 左
	    auto player1_0_1 = SpriteFrame::create("images/player1_tank/m"+lev+"-0-1.png", tankRect);
        auto player1_0_2 = SpriteFrame::create("images/player1_tank/m"+lev+"-0-2.png", tankRect);
        auto player1_0 = Animation::createWithSpriteFrames({ player1_0_1, player1_0_2 }, 0.05f);

        // 上
        auto player1_1_1 = SpriteFrame::create("images/player1_tank/m"+lev+"-1-1.png", tankRect);
        auto player1_1_2 = SpriteFrame::create("images/player1_tank/m"+lev+"-1-2.png", tankRect);
        auto player1_1 = Animation::createWithSpriteFrames({ player1_1_1, player1_1_2 }, 0.05f);
        // 右
        auto player1_2_1 = SpriteFrame::create("images/player1_tank/m"+lev+"-2-1.png", tankRect);
        auto player1_2_2 = SpriteFrame::create("images/player1_tank/m"+lev+"-2-2.png", tankRect);
        auto player1_2 = Animation::createWithSpriteFrames({ player1_2_1, player1_2_2 }, 0.05f);

        // 下
        auto player1_3_1 = SpriteFrame::create("images/player1_tank/m"+lev+"-3-1.png", tankRect);
        auto player1_3_2 = SpriteFrame::create("images/player1_tank/m"+lev+"-3-2.png", tankRect);
        auto player1_3 = Animation::createWithSpriteFrames({ player1_3_1, player1_3_2 }, 0.05f);

	    // 添加到缓存
        spriteFrameCache->addSpriteFrame(player1_0_1, "player1_0_" + lev);
        spriteFrameCache->addSpriteFrame(player1_1_1, "player1_1_" + lev);
        spriteFrameCache->addSpriteFrame(player1_2_1, "player1_2_" + lev);
        spriteFrameCache->addSpriteFrame(player1_3_1, "player1_3_" + lev);

        // 保存
        animations[0].pushBack(Animate::create(player1_0));
        animations[1].pushBack(Animate::create(player1_1));
        animations[2].pushBack(Animate::create(player1_2));
        animations[3].pushBack(Animate::create(player1_3));
	}

}

void PlayerTank::__initBullets() {
    TankBase::__initBullets();
    auto bullet2 = Bullet::create();
    bullets.pushBack(bullet2);
}

void PlayerTank::shoot() {
    auto bullet1 = bullets.at(0);
    auto bullet2 = bullets.at(1);

    if (!bullet1->isVisible() && !bullet2->isVisible()) {
        __shoot(bullet1);
    } else if (bullet1->isVisible() && bullet2->isVisible()) {
        // do nothing
    } else if (level >= 2) {
        // 此时可发射两枚子弹
        if (bullet1->isVisible()) {
            __shoot(bullet2);
        } else {
            __shoot(bullet1);
        }
    }
}
