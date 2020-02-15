#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "TankBase.h"

class TankBase;

class MapLayer : public cocos2d::LayerColor {
public:
	bool init() override;

	static MapLayer* getInstance();            // 得到地图图层实例

	void loadLevelData(int stage);             // 加载指定关卡的数据

	TankBase* getPlayer1();                    // 得到玩家1
	Block* getCamp();                          // 得到大本营
	cocos2d::Vector<Block*>& getAllBlocks();   // 得到所有方块

	void addPlayer();                          // 添加玩家
	void addEnemies();                         // 添加敌人

private:
	CREATE_FUNC(MapLayer);                     // 单例对象

	void __addSpriteFrameCache();              // 加载精灵缓存
	cocos2d::Vector<Block*> blocks;            // 管理所有方块
	cocos2d::Vector<TankBase*> players;        // 管理玩家坦克
	cocos2d::Vector<TankBase*> enemies;        // 管理敌方坦克
};