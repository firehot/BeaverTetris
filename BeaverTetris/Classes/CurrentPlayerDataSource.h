#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GameStructures.h"

class CurrentPlayerDataSource :public ServiceInterface
{
public:
	CurrentPlayerDataSource();
	~CurrentPlayerDataSource();

	bool isThereCurentPlayer();
	std::string getPlayerName();
	int getPlayerScore();
	int getPlayerCompletedLevelsCount();
	int getPlayerAvailableSpellsCount();
	int getSelectedGameLevelIndex();

	void setNewPlayerWithName(std::string aNewPlayerName);
	void setPlayerScore(int aPlayerScore);
	void completeLevel(std::string aCompletedLevelName);
	void setSelectedGameLevelIndex(int aGameLevelIndex);

	void cleanPlayer();

private:
	std::vector <std::string> _completedLevelsNames;
	bool _isThereCurentPlayer;
	PlayerInformation _playerData;
	int _selectedGameLevelIndex;
};

