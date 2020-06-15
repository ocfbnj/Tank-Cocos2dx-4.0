#pragma once

#include "cocos2d.h"
#include "TankBase.h"


class PlayerTank : public TankBase {
public:
	bool init() override;

	void setDir(Dir d) override;
    void shoot() override;

	void setBeControl(bool b = true);
	bool isBeControl();

	CREATE_FUNC(PlayerTank);

private:
	bool beControl = false;

	void __initSpriteFrameCache() override;
    void __initBullets() override;
};
