#pragma once

#include "cocos2d.h"
#include "Common.h"
#include <map>

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    static void addSpriteFrameCache();
    void updateInformationArea(bool first = false);                // 更新右侧信息区域

    static GameScene* create(int stage = 1) {
        auto* pRet = new(std::nothrow) GameScene();
        if (pRet) {
            if (stage == 0 || stage == 12 || stage == 14 || stage == 16 || stage == 30)
                stage++; // 地图数据有问题
            pRet->stage = stage;
            if (pRet->init()) {
                pRet->autorelease();
                return pRet;
            }
        }

        delete pRet;
        pRet = nullptr;

        return nullptr;
    }

    short stage = 1;                                          // 当前关卡

private:
    MapLayer* map = nullptr;                                  // 管理地图
    std::map<
        cocos2d::EventKeyboard::KeyCode, Dir> table;          // 键位方向表

    void __showLoadAnimate();                                 // 展示载入关卡动画
    void __initMapLayer();                                    // 初始化地图数据
    void __enableKeyListener();                               // 启动键盘监听器
    void __addTouchButton();                                  // 添加触摸按钮
    void __checkGameStatus(float);                            // 检查游戏状态
    void __gameover(float);                                   // 游戏结束动画
};

