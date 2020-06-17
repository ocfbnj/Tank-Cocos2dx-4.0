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

    __initBullets();

    return true;
}

void TankBase::playAnimate() {
    if (!canMove) {
        return;
    }

    this->runAction(RepeatForever::create(__getAnimations()[int(dir)].at(level)));
}

void TankBase::stopAnimate() {
    if (!canMove) {
        return;
    }

    this->stopAllActions();
}

void TankBase::__initBullets() {
    auto bullet1 = Bullet::create();
    bullets.pushBack(bullet1);
}

void TankBase::__autoMove(float /*t*/) {
    if (!canMove) {
        return;
    }
    // 1. 移动时检测和地图边缘的碰撞
    // 2. 移动时检测和方块的碰撞
    // 3. 移动时检测和坦克的碰撞

    auto position = this->getPosition();
    auto step = 1.0f + level * 0.2f;

    // 假设可以移动
    switch (dir) {
    case Dir::LEFT:
        this->setPositionX(position.x - step);
        break;
    case Dir::UP:
        this->setPositionY(position.y + step);
        break;
    case Dir::RIGHT:
        this->setPositionX(position.x + step);
        break;
    case Dir::DOWN:
        this->setPositionY(position.y - step);
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

void TankBase::birthAnimation(std::string afterStart) {
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;
    for (int i = 0; i < 4 * 2; i++) {
        std::string n = std::to_string(i % 4);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("star_" + n);
        spriteFrames.pushBack(spriteFrame);
    }

    // 星星动画
    auto animation = Animation::createWithSpriteFrames(spriteFrames, 0.2f);
    auto animate = Animate::create(animation);

    this->runAction(Sequence::create(
        animate,
        CallFunc::create([=]() {
        this->initWithSpriteFrameName(afterStart);
        canMove = true;
        this->beInvincible(3);
    }),
        nullptr
        ));
}

void TankBase::beInvincible(int time) {
    this->isInvincible = true;
    auto ring = Sprite::create();
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;
    for (int i = 0; i < 2 * time * 5; i++) {
        std::string n = std::to_string(i % 2);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("ring_" + n);
        spriteFrames.pushBack(spriteFrame);
    }
    auto animation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
    auto animate = Animate::create(animation);
    this->addChild(ring);
    ring->setAnchorPoint(Vec2(0, 0));
    ring->setPosition(0, 0);
    ring->runAction(Sequence::create(
        animate,
        CallFunc::create([=]() {
        ring->removeFromParent();
        this->isInvincible = false;
    })
        , nullptr
        ));
}

void TankBase::addSpriteFrameCache() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    // 坦克爆炸帧动画
    auto* blast_0 = Sprite::create("images/blast/0.png")->getSpriteFrame();
    auto* blast_1 = Sprite::create("images/blast/1.png")->getSpriteFrame();
    auto* blast_2 = Sprite::create("images/blast/2.png")->getSpriteFrame();
    auto* blast_3 = Sprite::create("images/blast/3.png")->getSpriteFrame();
    auto* blast_4 = Sprite::create("images/blast/4.png")->getSpriteFrame();

    blast_0->getTexture()->setAliasTexParameters();
    blast_1->getTexture()->setAliasTexParameters();
    blast_2->getTexture()->setAliasTexParameters();
    blast_3->getTexture()->setAliasTexParameters();
    blast_4->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(blast_0, "blast_0");
    spriteFrameCache->addSpriteFrame(blast_1, "blast_1");
    spriteFrameCache->addSpriteFrame(blast_2, "blast_2");
    spriteFrameCache->addSpriteFrame(blast_3, "blast_3");
    spriteFrameCache->addSpriteFrame(blast_4, "blast_4");

    // 坦克出生前的星星帧动画
    auto star_0 = Sprite::create("images/star0.png")->getSpriteFrame();
    auto star_1 = Sprite::create("images/star1.png")->getSpriteFrame();
    auto star_2 = Sprite::create("images/star2.png")->getSpriteFrame();
    auto star_3 = Sprite::create("images/star3.png")->getSpriteFrame();

    star_0->getTexture()->setAliasTexParameters();
    star_1->getTexture()->setAliasTexParameters();
    star_2->getTexture()->setAliasTexParameters();
    star_3->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(star_0, "star_0");
    spriteFrameCache->addSpriteFrame(star_1, "star_1");
    spriteFrameCache->addSpriteFrame(star_2, "star_2");
    spriteFrameCache->addSpriteFrame(star_3, "star_3");

    // 坦克保护环帧动画
    auto ring_0 = Sprite::create("images/ring0.png")->getSpriteFrame();
    auto ring_1 = Sprite::create("images/ring1.png")->getSpriteFrame();

    ring_0->getTexture()->setAliasTexParameters();
    ring_1->getTexture()->setAliasTexParameters();

    spriteFrameCache->addSpriteFrame(ring_0, "ring_0");
    spriteFrameCache->addSpriteFrame(ring_1, "ring_1");
}

void TankBase::shoot() {
    if (!canMove) {
        return;
    }

    auto bullet = bullets.at(0);
    if (!bullet->isVisible()) {
        __shoot(bullet);
    }
}

cocos2d::Vector<Bullet*>& TankBase::getAllBullets() {
    return bullets;
}

Bullet* TankBase::getBullet1() {
    return bullets.at(0);
}

void TankBase::__shoot(Bullet* bullet) {
    // AudioEngine::play2d("music/shoot.mp3");
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
