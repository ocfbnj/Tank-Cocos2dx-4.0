#pragma once

#include "cocos2d.h"

class MapLayer;

class GameScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	bool init() override;
	
	CREATE_FUNC(GameScene);

private:
	MapLayer* map;                                // 管理地图

	void __showLoadAnimate();                     // 展示载入关卡动画
	void __initMapLayer();                        // 初始化地图数据
	void __enableKeyListener();                   // 启动键盘监听器

	short stage = 1;                              // 当前关卡
};

