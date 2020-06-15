#include "GameScene.h"
#include "MapLayer.h"
#include "Common.h"
#include "AudioEngine.h"
#include "PlayerTank.h"

USING_NS_CC;

Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::init())
        return false;

    // 初始化表
    table[EventKeyboard::KeyCode::KEY_A] = Dir::LEFT;
    table[EventKeyboard::KeyCode::KEY_W] = Dir::UP;
    table[EventKeyboard::KeyCode::KEY_D] = Dir::RIGHT;
    table[EventKeyboard::KeyCode::KEY_S] = Dir::DOWN;

    // 将背景色设置为灰色
    auto background = LayerColor::create(Color4B(100, 100, 100, 200));
    this->addChild(background);

    // 播放开始音乐
    /*AudioEngine::setFinishCallback(AudioEngine::play2d("music/start.mp3"),
        [](int, const std::string &) {
            AudioEngine::play2d("music/bk_sound.mp3", true);
        });*/

        // 展示加载动画
    __showLoadAnimate();

    return true;
}

void GameScene::__showLoadAnimate() {
    auto width = Director::getInstance()->getVisibleSize().width;
    auto mid = Director::getInstance()->getVisibleSize().height / 2;
    auto block1 = LayerColor::create(Color4B(0, 0, 0, 255));
    auto block2 = LayerColor::create(Color4B(0, 0, 0, 255));

    this->addChild(block1);
    this->addChild(block2);

    //从上往下
    block1->setContentSize(Size(width, mid));
    block1->setPosition(Vec2(0, mid * 2));

    //从下往上
    block2->setContentSize(Size(width, mid));
    block2->setPosition(Vec2(0, -mid));

    auto delayTime = 0.5f;

    auto action1 = MoveBy::create(delayTime, Vec2(0, -mid));
    auto action2 = MoveBy::create(delayTime, Vec2(0, mid));

    block1->runAction(Sequence::create(action1, CallFunc::create([=]() {
        this->removeChild(block1);
    }), nullptr));

    block2->runAction(Sequence::create(action2, CallFunc::create([=]() {
        this->removeChild(block2);
    }), nullptr));


    // 展示Stage
    auto label = Label::createWithSystemFont("Stage " + std::to_string(stage), "Fira Code", 10);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Director::getInstance()->getVisibleSize() / 2);
    label->setVisible(false);
    this->addChild(label);

    label->runAction(Sequence::create(
        DelayTime::create(delayTime),
        Show::create(),
        DelayTime::create(1),
        CallFunc::create([=]() {
        this->removeChild(label);
        this->__initMapLayer();
        this->__enableKeyListener();
        this->__addTouchButton();
    }),
        nullptr)
    );
}

void GameScene::__initMapLayer() {
    map = MapLayer::getInstance();

    // map->loadLevelData(stage);
    map->loadLevelData(10);

    map->addPlayer();
    // map->addEnemies();

    this->addChild(map);

    // 设置地图位置
    map->setContentSize(Size(CENTER_WIDTH, CENTER_HEIGHT));
    map->setIgnoreAnchorPointForPosition(false);
    map->setAnchorPoint(Vec2(0, 0));
    map->setPosition(Vec2(CENTER_X, CENTER_Y));
}

void GameScene::__enableKeyListener() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*) {
        auto player1 = static_cast<PlayerTank*>(map->getPlayer1());
        switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            player1->setDir(table[keyCode]);
            player1->playAnimate();
            player1->startMove();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_J:
            player1->shoot();
            break;
        default:
            break;
        }

    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event*) {
        auto player1 = static_cast<PlayerTank*>(map->getPlayer1());
        switch (keyCode) {
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
        case cocos2d::EventKeyboard::KeyCode::KEY_W:
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            player1->stopAnimate();
            player1->stopMove();
            break;
        default:
            break;
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::__addTouchButton() {
    auto btn_left = Sprite::create("images/move_left.png");
    auto btn_up = Sprite::create("images/move_up.png");
    auto btn_right = Sprite::create("images/move_right.png");
    auto btn_down = Sprite::create("images/move_down.png");

    this->addChild(btn_left);
    this->addChild(btn_up);
    this->addChild(btn_right);
    this->addChild(btn_down);

    btn_left->setPosition(15, WINDOW_HEIGHT - 180);
    btn_up->setPosition(37.5f, WINDOW_HEIGHT - 160);
    btn_right->setPosition(60, WINDOW_HEIGHT - 180);
    btn_down->setPosition(37.5f, WINDOW_HEIGHT - 200);

    auto touchListener = EventListenerTouchOneByOne::create();

    touchListener->onTouchBegan = [=](Touch* touch, Event*) {
        auto point = touch->getLocation();
        auto player1 = static_cast<PlayerTank*>(map->getPlayer1());
        bool isMove = false;

        if (btn_left->getBoundingBox().containsPoint(point)) {
            player1->setDir(Dir::LEFT);
            isMove = true;
        } else if (btn_up->getBoundingBox().containsPoint(point)) {
            player1->setDir(Dir::UP);
            isMove = true;
        } else if (btn_right->getBoundingBox().containsPoint(point)) {
            player1->setDir(Dir::RIGHT);
            isMove = true;
        } else if (btn_down->getBoundingBox().containsPoint(point)) {
            player1->setDir(Dir::DOWN);
            isMove = true;
        } else {
            player1->shoot();
        }

        if (isMove) {
            player1->playAnimate();
            player1->startMove();
        }

        return true;
    };

    touchListener->onTouchEnded = [=](Touch* touch, Event*) {
        auto point = touch->getLocation();
        auto player1 = static_cast<PlayerTank*>(map->getPlayer1());
        if (btn_left->getBoundingBox().containsPoint(point)
            || btn_up->getBoundingBox().containsPoint(point)
            || btn_right->getBoundingBox().containsPoint(point)
            || btn_down->getBoundingBox().containsPoint(point)) {

            player1->stopAnimate();
            player1->stopMove();
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
