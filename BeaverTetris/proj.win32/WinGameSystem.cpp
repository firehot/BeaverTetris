#include "WinGameSystem.h"
#include "EventDispatcher.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameEventsFactory.h"
#include "GameDesignConstants.h"

using namespace std;

WinGameSystem::WinGameSystem(CurrentPlayerDataSource *aCurrentPlayerDataSource, CurrentLevelDataSource *aCurrentLevelDataSource, GameBoard *aGameBoard)
{
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_currentLevelDataSource = aCurrentLevelDataSource;
	_gameBoard = aGameBoard;
}


WinGameSystem::~WinGameSystem(void)
{
}


void WinGameSystem::updateSystem(float deltaTime)
{

	EventDispatcher *eventDispatcher = (EventDispatcher*)ServiceLocator::getServiceForKey(eventDispatcherKey);

	if (_currentLevelDataSource->winGameResult)
	{
		int awardForVictory = _currentLevelDataSource->getCurrentLevelAward;
		int currentPlayerScore = _currentPlayerDataSource->getPlayerScore;
		_currentPlayerDataSource->setPlayerScore(currentPlayerScore + awardForVictory);

		string winLevelName = _currentLevelDataSource->getCurrentLevelName;
		_currentPlayerDataSource->completeLevel(winLevelName);

		if (_currentLevelDataSource->winAllGameResult)
		{
			eventDispatcher->handleEvent(GameEventsFactory::makeGoToPopUpEventWithKey(kWinAllGamePopUp));
		}
		else
		{
			eventDispatcher->handleEvent(GameEventsFactory::makeGoToPopUpEventWithKey(kWinGamePopUp));
		}

	}
	else
	{
		if (loseGameChecker)
		{
			eventDispatcher->handleEvent(GameEventsFactory::makeGoToPopUpEventWithKey(kLoseGameUp));
		}
	}

}

bool WinGameSystem::loseGameChecker()
{

	int downLoseZoneY = _gameBoard->getGameBoardHeight - standartDetailHeight;
	int upLoseZoneY = _gameBoard->getGameBoardHeight;

	bool isThereTetraminoInLoseZone = false;

	for (int yIndex = downLoseZoneY; yIndex < upLoseZoneY; yIndex++)
	{

		for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth; xIndex++)
		{
			Tetramino *tetraminoIngameBoard = _gameBoard->getTetraminoForXYposition(xIndex, yIndex);

			if (tetraminoIngameBoard->getTetraminoType > kTetraminoEmpty)
			{
				isThereTetraminoInLoseZone = true;
				return isThereTetraminoInLoseZone;
			}

		}

	}

	return isThereTetraminoInLoseZone;

}