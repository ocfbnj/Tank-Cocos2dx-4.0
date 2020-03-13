#include "GameScene.h"
#include "MapLayer.h"
#include "Common.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene() {
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
   /* AudioEngine::setFinishCallback(AudioEngine::play2d("music/start.mp3"),
        [](auto, auto) {
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
            }),
            nullptr)
    );
}

void GameScene::__initMapLayer() {
    map = MapLayer::getInstance();
    
    map->loadLevelData(stage);
    map->addPlayer();

    this->addChild(map);
    map->setContentSize(Size(CENTER_WIDTH, CENTER_HEIGHT));
    map->setIgnoreAnchorPointForPosition(false);
    map->setAnchorPoint(Vec2(0, 0));
    map->setPosition(Vec2(CENTER_X, CENTER_Y));
}

void GameScene::__enableKeyListener() {
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*) {
        auto player1 = map->getPlayer1();
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
        auto player1 = map->getPlayer1();
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
