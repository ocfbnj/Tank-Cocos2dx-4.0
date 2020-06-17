#include "Common.h"

#include "PlayerTank.h"
#include "MapLayer.h"
#include "PlayerBullet.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Vector<cocos2d::Animate*> PlayerTank::animations[4]{};

bool PlayerTank::init() {
    if (!TankBase::init()) {
        return false;
    }

    // 玩家出生时血量为3
    blood = 3;

    // 展示出生动画
    birth("player1_1_" + std::to_string(level));

    // 玩家出生时方向向上
    dir = Dir::UP;

    return true;
}

void PlayerTank::setDir(Dir d) {
    if (!canMove) return;

    if (d == dir) {
        return;
    }

    dir = d;

    // 当改变方向时，将坐标调整为最接近于8的倍数
    __adjustPosition();

    std::string name = "player1_" + std::to_string((int)dir) + "_"
        + std::to_string(level);

    // 更换图片
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
}

void PlayerTank::__initBullets() {
    // 玩家最多拥有两颗子弹
    auto bullet1 = PlayerBullet::create();
    auto bullet2 = PlayerBullet::create();
    bullets.pushBack(bullet1);
    bullets.pushBack(bullet2);
}

void PlayerTank::loadFrameAnimation() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();

    Rect tankRect(0, 0, TANK_SIZE, TANK_SIZE);

    // 总共4个等级
    for (int i = 0; i < 4; i++) {
        std::string lev = std::to_string(i);
        // 总共4个方向
        for (int j = 0; j < 4; j++) {
            std::string d = std::to_string(j);
            auto player1_1 = SpriteFrame::create("images/player1_tank/m" + lev + "-" + d + "-1.png", tankRect);
            auto player1_2 = SpriteFrame::create("images/player1_tank/m" + lev + "-" + d + "-2.png", tankRect);
            auto player1 = Animation::createWithSpriteFrames({ player1_1, player1_2 }, 0.05f);

            player1_1->getTexture()->setAliasTexParameters();
            player1_2->getTexture()->setAliasTexParameters();

            // 添加到缓存
            spriteFrameCache->addSpriteFrame(player1_1, "player1_" + d + "_" + lev);

            // 保存
            animations[j].pushBack(Animate::create(player1));
        }
    }
}

const cocos2d::Vector<cocos2d::Animate*>* PlayerTank::__getAnimations() {
    return animations;
}

void PlayerTank::shoot() {
    if (!canMove) {
        return;
    }

    auto bullet1 = bullets.at(0);
    auto bullet2 = bullets.at(1);

    if (!bullet1->isVisible() && !bullet2->isVisible()) {
        bullet1->setLevel(level);
        __shoot(bullet1);
    } else if (bullet1->isVisible() && bullet2->isVisible()) {
        // 什么都不做
    } else if (level >= 2) {
        // 此时可发射两枚子弹
        if (bullet1->isVisible()) {
            bullet2->setLevel(level);
            __shoot(bullet2);
        } else {
            bullet1->setLevel(level);
            __shoot(bullet1);
        }
    }
}

void PlayerTank::setBeControl(bool b) {
    beControl = b;
}

bool PlayerTank::isBeControl() {
    return beControl;
}

void PlayerTank::disBlood() {
    if (isInvincible)
        return;

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> spriteFrames;

    for (int i = 0; i != 5; i++) {
        std::string n = std::to_string(i);
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName("blast_" + n);
        spriteFrames.pushBack(spriteFrame);
    }

    // TODO 每次死亡都重新构造动画
    auto blastAnimation = Animation::createWithSpriteFrames(spriteFrames, 0.1f);
    auto blastanimate = Animate::create(blastAnimation);

    // 播放音效
    AudioEngine::play2d("music/enemy-bomb.mp3");

    if (--blood == 0) {
        // 移除该坦克
        auto& players = MapLayer::getInstance()->getPlayers();
        players.eraseObject(this);

        // 播放动画
        this->runAction(
            Sequence::create(
                blastanimate,
                CallFunc::create([this] {
            this->removeFromParentAndCleanup(true);
        }),
                nullptr
            ));
    } else {
        // 播放动画
        this->runAction(
            Sequence::create(
                blastanimate,
                CallFunc::create([this] {
            // 回到出生点
            birth("player1_" + std::to_string((int)dir) + "_" + std::to_string(level));
        }),
                nullptr
            ));
    }
}
