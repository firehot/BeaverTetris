#include "MainGamePauseViewController.h"
#include "GameViewStyleHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "GameAnimationActionsConstants.h"
#include "WinGameSystem.h"
#include "MainGamePauseDelegate.h"
#include "GameStatesHelper.h"

using namespace cocos2d;

MainGamePauseViewController::MainGamePauseViewController(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	setPauseView();
	setUpKeyboard();

	MainGamePauseDelegate *mainGamePauseDelegate = (MainGamePauseDelegate*)ServiceLocator::getServiceForKey(mainGamePauseDelegateKey);
	mainGamePauseDelegate->addObserver(this);
}


MainGamePauseViewController::~MainGamePauseViewController(void)
{
}

void MainGamePauseViewController::setUpKeyboard()
{
	cocos2d::EventListenerKeyboard *keyboardListner = cocos2d::EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(MainGamePauseViewController::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
	_eventListenerKeyboard = keyboardListner;
}

void MainGamePauseViewController::setPauseView()
{
	Sprite *pauseView = Sprite::create("HelloWorld.png");
	pauseView->setScaleY(0.06f);
	pauseView->setScaleX(0.04f);
	pauseView->setColor(Color3B::GREEN);
	this->addChild(pauseView);
}

void MainGamePauseViewController::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	if (aKeyCode == EventKeyboard::KeyCode::KEY_P && _winGameSystem->gameEnded() == false)
	{
		_eventListenerKeyboard->setEnabled(false);
		_gameTimeStepController->setUpdateAvailable(false);
		function<void()> callback = [](){ GameStatesHelper::goToPopUp(kPauseGamePopUp);};
		GameViewStyleHelper::runButtonActionWithCallbackAndDuration(this ,callback, gameControllButtonActionDuration);
	}
}

void MainGamePauseViewController::pauseWasEnded()
{
	_eventListenerKeyboard->setEnabled(true);
}