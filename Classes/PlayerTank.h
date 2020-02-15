#pragma once

#include "cocos2d.h"
#include "TankBase.h"


class PlayerTank : public TankBase {
public:
	bool init() override;

	void setDir(Dir d) override;
    void shoot() override;

	CREATE_FUNC(PlayerTank);

private:
	void __initSpriteFrameCache() override;
    void __initBullets() override;
};
