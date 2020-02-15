#pragma once

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init() override;

	CREATE_FUNC(MenuScene);

private:
	cocos2d::Sprite* background;                                      //±³¾°Í¼Æ¬
	cocos2d::Sprite* selector;                                        //²Ëµ¥Ñ¡ÔñÆ÷

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode,        //ÒÆ¶¯¹â±ê
		cocos2d::Event* event);

	void __initBackground();
	void __initSelector();

	cocos2d::Animate* __getAnimFrams();
};
