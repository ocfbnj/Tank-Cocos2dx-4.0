#pragma once

#include "cocos2d.h"
#include "TankBase.h"


class PlayerTank : public TankBase {
public:
	bool init() override;

	void setDir(Dir d);

	CREATE_FUNC(PlayerTank);

private:
	void __initSpriteFrameCache() override;
};
