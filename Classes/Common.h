#pragma once

// 边框大小
#define BORDER_WIDTH 100

//窗口大小
#define WINDOW_WIDTH	(256 + BORDER_WIDTH)
#define WINDOW_HEIGHT	224

//箭头位置
#define ARROWS_X        75
#define ARROWS_Y        132
#define ARROWS_DIS      15

//中间黑色游戏区域
#define CENTER_WIDTH	208
#define CENTER_HEIGHT	208

//游戏区域相对左下角的坐标
#define CENTER_X		((WINDOW_WIDTH - CENTER_WIDTH) / 2)
#define CENTER_Y		(WINDOW_HEIGHT - CENTER_HEIGHT)

//方块大小
#define BLOCK_SIZE      8

//坦克大小
#define TANK_SIZE       16

// 坦克初始位置
#define PLAYER1_START_X 80
#define PLAYER1_START_Y 8

#define PLAYER2_START_X 128
#define PLAYER2_START_Y 8

// 大本营位置
#define CAMP_X          104
#define CAMP_Y          8

//子弹大小
#define BULLET_SIZE     4

enum class Dir {
	LEFT = 0, UP, RIGHT, DOWN
};
