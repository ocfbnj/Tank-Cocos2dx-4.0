#include "TankBase.h"
#include "Common.h"
#include "MapLayer.h"
#include "Bullet.h"
#include "Block.h"

USING_NS_CC;

bool TankBase::init() {
	if (!Sprite::init()) {
		return false;
	}

	__initSpriteFrameCache();
	__initBullets();

	return true;
}

void TankBase::playAnimate() {
	this->runAction(RepeatForever::create(animations.at((int)dir)));

}

void TankBase::stopAnimate() {
	this->stopAllActions();
}

void TankBase::moveLeft() {
	setDir(Dir::LEFT);
}

void TankBase::moveUp() {
	setDir(Dir::UP);
}

void TankBase::moveRight() {
	setDir(Dir::RIGHT);
}

void TankBase::moveDown() {
	setDir(Dir::DOWN);
}

void TankBase::__initBullets() {
	auto bullet1 = Bullet::create();
	bullets.pushBack(bullet1);
}

void TankBase::__autoMove(float t) {
	// 1. 移动时检测和地图边缘的碰撞
	// 2. 移动时检测和方块的碰撞
	// 3. 移动时检测和坦克的碰撞

	auto position = this->getPosition();

	// 假设可以移动
	switch (dir) {
	case Dir::LEFT:
		this->setPositionX(position.x - 1);
		break;
	case Dir::UP:
		this->setPositionY(position.y + 1);
		break;
	case Dir::RIGHT:
		this->setPositionX(position.x + 1);
		break;
	case Dir::DOWN:
		this->setPositionY(position.y - 1);
		break;
	default:
		break;
	}

	// 如果产生碰撞，则回到移动之前的位置
	if (__isBlockIntersection() || __isMapIntersection() || __isTankIntersection()) {
		this->setPosition(position);
	}
}

void TankBase::__adjustPosition() {
	this->setPositionX(__adjustNumber(this->getPositionX()));
	this->setPositionY(__adjustNumber(this->getPositionY()));
}

int TankBase::__adjustNumber(int number) {
	if (number % 8 != 0) {
		for (int offset = 1; offset < 8; offset++) {
			if ((number + offset) % 8 == 0) {
				return number + offset;
			}

			if ((number - offset) % 8 == 0) {
				return number - offset;
			}
		}
	}

	return number;
}

bool TankBase::__isMapIntersection() {
	auto position = this->getPosition();
	if (position.x - TANK_SIZE / 2 < 0
		|| position.y + TANK_SIZE / 2 > CENTER_HEIGHT
		|| position.x + TANK_SIZE / 2 > CENTER_WIDTH
		|| position.y - TANK_SIZE / 2 < 0) {
		return true;
	}
	return false;
}

bool TankBase::__isBlockIntersection() {
	// 得到所有方块位置
	auto& blocks = MapLayer::getInstance()->getAllBlocks();
	auto box = getBoundingBox();
	for (auto& block : blocks) {
		auto category = block->getCategory();
		if (category == BlockCategory::OBSTACLE || category == BlockCategory::RIVER) {
			auto other = block->getBoundingBox();
			if (box.myIntersectsRect(other)) {
				return true;
			}
		}
	}
	return false;
}

bool TankBase::__isTankIntersection() {
	// TODO
	return false;
}

void TankBase::startMove() {
	this->schedule(CC_SCHEDULE_SELECTOR(TankBase::__autoMove), 0.02f);
}

void TankBase::stopMove() {
	this->unschedule(CC_SCHEDULE_SELECTOR(TankBase::__autoMove));
}

void TankBase::shoot() {
	for (auto& bullet : bullets) {
		if (!bullet->isVisible()) {
			auto position = this->getPosition();
			switch (dir) {
			case Dir::LEFT:
				bullet->setSpriteFrame("bullet_l");
				bullet->setPosition(position.x - TANK_SIZE / 2, position.y);
				break;
			case Dir::UP:
				bullet->setSpriteFrame("bullet_u");
				bullet->setPosition(position.x, position.y + TANK_SIZE / 2);
				break;
			case Dir::RIGHT:
				bullet->setSpriteFrame("bullet_r");
				bullet->setPosition(position.x + TANK_SIZE / 2, position.y);
				break;
			case Dir::DOWN:
				bullet->setSpriteFrame("bullet_d");
				bullet->setPosition(position.x, position.y - TANK_SIZE / 2);
				break;
			default:
				break;
			}

			bullet->setDir(dir);
			bullet->setVisible(true);
			bullet->startMove();
		}
	}
}

cocos2d::Vector<Bullet*>& TankBase::getAllBullets() {
	return bullets;
}

