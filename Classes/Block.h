#pragma once

#include "Common.h"
#include "cocos2d.h"
#include <utility>

// 方块分类
enum class BlockCategory {
    OBSTACLE,                     // 坦克不能通过，子弹可以摧毁
    NON_OBSTACLE,                 // 坦克可以通过，子弹不能摧毁
    RIVER                         // 坦克不能通过，子弹不能摧毁
};

// 方块类型
enum class BlockType {
    CAMP,
    FOREST,
    ICE,
    RIVER,
    STONE,
    WALL,
    UNDIFINE
};

class Block : public cocos2d::Sprite {
public:
    bool init() override;             // 调用父类的init

    virtual BlockCategory getCategory() = 0;
    virtual BlockType getType() { return BlockType::UNDIFINE; }

    static void addSpriteFrameCache();
};

class __Obstacle : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::OBSTACLE; }
};

class __NonObstacle : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::NON_OBSTACLE; }
};

class __River : public Block {
public:
    BlockCategory getCategory() override { return BlockCategory::RIVER; }
};

class BlockCamp : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::CAMP; }

    CREATE_FUNC(BlockCamp);
};

class BlockWall : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::WALL; }

    std::pair<bool, bool> destory(Dir d, const cocos2d::Rect& box);

    CREATE_FUNC(BlockWall);

private:
    cocos2d::LayerColor* blacks[4]{};        // 4个黑色方块，用于遮挡
    bool __isDestory();                      // 检测方块是否被摧毁
};

class BlockStone : public __Obstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::STONE; }

    CREATE_FUNC(BlockStone);
};

class BlockForest : public __NonObstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::FOREST; }

    CREATE_FUNC(BlockForest);
};

class BlockIce : public __NonObstacle {
public:
    bool init() override;
    BlockType getType() override { return BlockType::ICE; }

    CREATE_FUNC(BlockIce);
};

class BlockRiver : public __River {
public:
    bool init() override;
    BlockType getType() override { return BlockType::RIVER; }

    CREATE_FUNC(BlockRiver);
};
