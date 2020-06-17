#pragma once

#include "cocos2d.h"
#include "Common.h"
#include <map>

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    bool init() override;

    CREATE_FUNC(GameScene);

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

