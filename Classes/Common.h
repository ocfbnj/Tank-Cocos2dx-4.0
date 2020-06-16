#pragma once

// 以下为设计尺寸

// 窗口大小
constexpr float WINDOW_WIDTH = 256;
constexpr float WINDOW_HEIGHT = 224;

// 箭头位置
constexpr float ARROWS_X = 75;
constexpr float ARROWS_Y = 132;
constexpr float ARROWS_DIS = 15;

// 中间黑色游戏区域大小
constexpr float CENTER_WIDTH = 208;
constexpr float CENTER_HEIGHT = 208;

// 方块大小
constexpr float BLOCK_SIZE = 8;

// 坦克大小
constexpr float TANK_SIZE = 16;

// 坦克初始位置
constexpr float PLAYER1_START_X = 80;
constexpr float PLAYER1_START_Y = 8;

constexpr float PLAYER2_START_X = 128;
constexpr float PLAYER2_START_Y = 8;

// 大本营位置
constexpr float CAMP_X = 104;
constexpr float CAMP_Y = 8;

// 子弹大小
constexpr float BULLET_SIZE = 4;

enum class Dir {
    LEFT = 0, UP, RIGHT, DOWN
};
