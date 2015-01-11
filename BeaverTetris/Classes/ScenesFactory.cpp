#include "ScenesFactory.h"
#include "SceneFactory.h"

#include "LoadingGameSceneFactory.h"

using namespace std;
using namespace cocos2d;

ScenesFactory::ScenesFactory(void)
{
	_scenesFactories = getScenesFactories();
}


ScenesFactory::~ScenesFactory(void)
{
}

CCScene* ScenesFactory::getGameSceneForId(GameState aSceneId)
{
	SceneFactory *sceneFactory = _scenesFactories[aSceneId];
	return sceneFactory->createScene();
}

std::map<GameState, SceneFactory*> ScenesFactory::getScenesFactories()
{
	map<GameState, SceneFactory*> scenesFactories;

	scenesFactories[kLoadGame] = new LoadingGameSceneFactory();

	return scenesFactories;
}



