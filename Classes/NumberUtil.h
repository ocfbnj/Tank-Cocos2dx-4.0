#pragma once

#include "cocos2d.h"

class NumberUtil {
public:
    static cocos2d::Sprite* getBlackNumber(int number) {
        cocos2d::Rect rect(number * 7.0f, 0.0f, 7.0f, 7.0f);
        auto sprite = cocos2d::Sprite::create("images/black-number.png", rect);
        sprite->getTexture()->setAliasTexParameters();

        return sprite;
    }

    static cocos2d::Sprite* getWhiteNumber(int number) {
        cocos2d::Rect rect(number * 7.0f, 0.0f, 7.0f, 7.0f);
        auto sprite = cocos2d::Sprite::create("images/white-number.png", rect);
        sprite->getTexture()->setAliasTexParameters();

        return sprite;
    }

    static cocos2d::Sprite* getYellowNumber(int number) {
        cocos2d::Rect rect(number * 7.0f, 0.0f, 7.0f, 7.0f);
        auto sprite = cocos2d::Sprite::create("images/yellow-number.png", rect);
        sprite->getTexture()->setAliasTexParameters();

        return sprite;
    }
};