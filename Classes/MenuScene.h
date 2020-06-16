#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;

    CREATE_FUNC(MenuScene);

private:
    cocos2d::Sprite* background;                                      // 背景图片
    cocos2d::Sprite* selector;                                        // 菜单选择器
    bool isSelectorInit;

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,        // 键盘移动光标
                      cocos2d::Event* event);
    bool onTouch(cocos2d::Touch* touch, cocos2d::Event*);             // 触摸移动光标


    void __initBackground();
    void __initSelector();

    cocos2d::Animate* __getAnimFrames();                              // 选择器帧动画
};
