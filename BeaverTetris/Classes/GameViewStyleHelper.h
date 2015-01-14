#pragma once

#include "cocos2d.h"
#include <functional>

class GameViewStyleHelper
{
public:
	GameViewStyleHelper(void);
	~GameViewStyleHelper(void);

	static void runStandardButtonActionWithCallback(cocos2d::CCNode *aButton, std::function<void()> aCallback);

};

