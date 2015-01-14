#include "StartGameMenuDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameStatesHelper.h"
#include "GameViewConstants.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"

using namespace std;
using namespace cocos2d;

StartGameMenuDataSource::StartGameMenuDataSource()
{

	_currentPlayerDataSource = (CurrentPlayerDataSource*) ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_menuItems = makeMenuItems();

}


StartGameMenuDataSource::~StartGameMenuDataSource()
{
}

vector <StartGameMenuItemInformation> StartGameMenuDataSource::makeMenuItems() 
{

	vector <StartGameMenuItemInformation> menuItems = vector <StartGameMenuItemInformation>();

	if (_currentPlayerDataSource->isThereCurentPlayer())
	{
		StartGameMenuItemInformation menuItem1;
		menuItem1.imageKey = gameElement1Key;
		//menuItem1.callback = [](){GameStatesHelper::goToScene(kSelectLevel);};
		menuItem1.callback = [](){CCLOG("kSelectLevel");};
		menuItems.push_back(menuItem1);
	}

	StartGameMenuItemInformation menuItem2;
	menuItem2.imageKey = gameElement2Key;
	//menuItem2.callback = [](){GameStatesHelper::goToScene(kSelectLevel);};
	menuItem2.callback = [](){CCLOG("kSelectLevel");};
    menuItems.push_back(menuItem2);

	StartGameMenuItemInformation menuItem3;
	menuItem3.imageKey = gameElement3Key;
	//menuItem3.callback = [](){GameStatesHelper::goToScene(kRecords);};
	menuItem3.callback = [](){CCLOG("kRecords");};
    menuItems.push_back(menuItem3);

	StartGameMenuItemInformation menuItem4;
	menuItem4.imageKey = gameElement4Key;
	//menuItem4.callback = [](){GameStatesHelper::goToPopUp(kRegulateSoundPopUp);};
	menuItem4.callback = [](){CCLOG("kRegulateSoundPopUp");};
    menuItems.push_back(menuItem4);

	StartGameMenuItemInformation menuItem5;
	menuItem5.imageKey = gameElement5Key;
	//menuItem5.callback = [](){GameStatesHelper::goToScene(kDevelopers);};
	menuItem5.callback = [](){CCLOG("kDevelopers");};
    menuItems.push_back(menuItem5);
	
	return menuItems;

}

int StartGameMenuDataSource::getMenuItemsCount()
{
	return _menuItems.size();
}

string StartGameMenuDataSource::getMenuImageForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return GameFileExtensionMaker::getGraphicWithExtension(item.imageKey);
}

Vec2 StartGameMenuDataSource::getMenuItemPositionForIndex(int aIndex)
{
	Vec2 position = Vec2(0, 0 - (startMenuItemOffsetY * aIndex));
	return position;
}

function<void()> StartGameMenuDataSource::getMenuItemCallbackForIndex(int aIndex)
{
	StartGameMenuItemInformation item = _menuItems[aIndex];
	return item.callback;
}

