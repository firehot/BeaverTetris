#pragma once

#include "SceneFactory.h"
#include "cocos2d.h"

class DevelopersSceneFactory : public SceneFactory
{
public:
	DevelopersSceneFactory(void);
	~DevelopersSceneFactory(void);

	virtual cocos2d::CCScene* createScene();

private:

	cocos2d::MenuItemImage* getCloseButton();

};

