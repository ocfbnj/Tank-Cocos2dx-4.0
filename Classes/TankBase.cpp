#include "TankBase.h"
#include "Common.h"
#include "MapLayer.h"
#include "Bullet.h"
#include "Block.h"

#include "AudioEngine.h"

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
    this->runAction(RepeatForever::create(animations[(int) dir].at(level)));

}

void TankBase::stopAnimate() {
    this->stopAllActions();
}

void TankBase::__initBullets() {
    auto bullet1 = Bullet::create();
    bullets.pushBack(bullet1);
}

void TankBase::__autoMove(float /*t*/) {
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
    this->setPositionX(__adjustNumber(int(this->getPositionX())));
    this->setPositionY(__adjustNumber(int(this->getPositionY())));
}

float TankBase::__adjustNumber(int number) {
    if (number % 8 != 0) {
        for (int offset = 1; offset < 8; offset++) {
            if ((number + offset) % 8 == 0) {
                return float(number + offset);
            }

            if ((number - offset) % 8 == 0) {
                return float(number - offset);
            }
        }
    }

    return float(number);
}

bool TankBase::__isMapIntersection() {
    auto position = this->getPosition();
    return position.x - TANK_SIZE / 2.0f < 0
           || position.y + TANK_SIZE / 2.0f > CENTER_HEIGHT
           || position.x + TANK_SIZE / 2.0f > CENTER_WIDTH
           || position.y - TANK_SIZE / 2.0f < 0;
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
    if (!isMove) {
        musicId = AudioEngine::play2d("music/player_move.mp3");
        this->schedule(CC_SCHEDULE_SELECTOR(TankBase::__autoMove), 0.02f);
        isMove = true;
    }
}

void TankBase::stopMove() {
    this->unschedule(CC_SCHEDULE_SELECTOR(TankBase::__autoMove));
    AudioEngine::stop(musicId);
    isMove = false;
}

void TankBase::shoot() {
    auto bullet = bullets.at(0);
    if (!bullet->isVisible()) {
        __shoot(bullet);
    }
}

cocos2d::Vector<Bullet*>& TankBase::getAllBullets() {
    return bullets;
}

void TankBase::__shoot(Bullet* bullet) {
    AudioEngine::play2d("music/shoot.mp3");
    auto position = this->getPosition();
    switch (dir) {
        case Dir::LEFT:
            bullet->setSpriteFrame("bullet_l");
            bullet->setPosition(position.x - TANK_SIZE / 2.0f, position.y);
            break;
        case Dir::UP:
            bullet->setSpriteFrame("bullet_u");
            bullet->setPosition(position.x, position.y + TANK_SIZE / 2.0f);
            break;
        case Dir::RIGHT:
            bullet->setSpriteFrame("bullet_r");
            bullet->setPosition(position.x + TANK_SIZE / 2.0f, position.y);
            break;
        case Dir::DOWN:
            bullet->setSpriteFrame("bullet_d");
            bullet->setPosition(position.x, position.y - TANK_SIZE / 2.0f);
            break;
        default:
            break;
    }

    bullet->setDir(dir);
    bullet->setVisible(true);
    bullet->startMove();
}

