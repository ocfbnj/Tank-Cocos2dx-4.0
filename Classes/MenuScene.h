#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;

    CREATE_FUNC(MenuScene);

private:
    cocos2d::Node* offsetNode = nullptr;                              // Æ«ÒÆ
    cocos2d::Sprite* background = nullptr;                            // ±³¾°Í¼Æ¬
    cocos2d::Sprite* selector = nullptr;                              // ²Ëµ¥Ñ¡ÔñÆ÷
    bool isSelectorInit = false;

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,        // ¼üÅÌÒÆ¶¯¹â±ê
                      cocos2d::Event* event);
    bool onTouch(cocos2d::Touch* touch, cocos2d::Event*);             // ´¥ÃþÒÆ¶¯¹â±ê


    void __initBackground();
    void __initSelector();

    cocos2d::Animate* __getAnimFrames();                              // Ñ¡ÔñÆ÷Ö¡¶¯»­
};
