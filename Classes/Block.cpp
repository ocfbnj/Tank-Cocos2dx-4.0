#include "Block.h"
#include "MapLayer.h"

USING_NS_CC;

bool Block::init() {
	if (!Sprite::init()) {
		return false;
	}

	return true;
}

bool BlockWall::init() {
	if (!Block::init()) {
		return false;
	}

	this->initWithSpriteFrameName("wall");

	// 创建4个遮挡精灵
	for (int i = 0; i < 4; i++) {
		blacks[i] = LayerColor::create(Color4B(0, 0, 0, 255), 4, 4);
		blacks[i]->setIgnoreAnchorPointForPosition(false);
		blacks[i]->setAnchorPoint(Vec2(0, 0));
		this->addChild(blacks[i]);
		blacks[i]->setVisible(false);

		blacks[i]->setPosition(Vec2(i / 2 * BLOCK_SIZE / 2.0f,
			i % 2 * BLOCK_SIZE / 2.0f));
	}

	return true;
}

std::pair<bool, bool> BlockWall::destory(Dir d, const Rect& box) {
	bool flag = false;
	auto position = this->getPosition();
	for (int i = 0; i < 4; i++) {
		// 转为坐标为相对于MapLayer的坐标
		auto preBox = blacks[i]->getBoundingBox();
		auto tranBox = Rect(preBox.getMinX() + position.x,
			preBox.getMinY() + position.y, 
			preBox.getMaxX() - preBox.getMinX(),
			preBox.getMaxY() - preBox.getMinY());

		// 加宽子弹
		Rect cmpBox;
		switch (d) {
		case Dir::LEFT:
		case Dir::RIGHT:
			cmpBox = Rect(box.getMinX(),box.getMinY() + 1 - BLOCK_SIZE, 
				BULLET_SIZE, TANK_SIZE);
			break;
		case Dir::UP:
		case Dir::DOWN:
			cmpBox = Rect(box.getMinX() + 1 - BLOCK_SIZE,
				box.getMinY(), TANK_SIZE, BULLET_SIZE);
			break;
		default:
			break;
		}

		if (!blacks[i]->isVisible()
			&& tranBox.intersectsRect(cmpBox)) {

			blacks[i]->setVisible(true);
			flag = true;
		}
	}

	return std::make_pair(flag, __isDestory());
}

bool BlockWall::__isDestory() {
	for (int i = 0; i < 4; i++) {
		if (!blacks[i]->isVisible()) {
			return false;
		}
	}

	return true;
}

bool BlockStone::init() {
	if (!Block::init()) {
		return false;
	}

	this->initWithSpriteFrameName("stone");

	return true;
}

bool BlockCamp::init() {
	if (!Block::init()) {
		return false;
	}

	this->initWithSpriteFrameName("camp_0");

	return true;
}

bool BlockForest::init() {
	if (!Block::init()) {
		return false;
	}

	this->initWithSpriteFrameName("forest");

	return true;
}

bool BlockIce::init() {
	if (!Block::init()) {
		return false;
	}

	this->initWithSpriteFrameName("ice");

	return true;
}

bool BlockRiver::init() {
	if (!Block::init()) {
		return false;
	}

	auto spriteFrameCache = SpriteFrameCache::getInstance();

	auto animation = Animation::createWithSpriteFrames({
		spriteFrameCache->getSpriteFrameByName("river_0"),
		spriteFrameCache->getSpriteFrameByName("river_1")
		},
		1.5f
	);

	auto animate = Animate::create(animation);

	this->runAction(RepeatForever::create(animate));

	return true;
}
