#pragma once

#include "GameSystemInterface.h"
#include "ServiceInterface.h"

class GameBoard;
class FullLineCombination;
class FillingGapInBoardSystem;
class SimilarTetraminosCombination;

class TetrisLogicSystem :public GameSystemInterface, public ServiceInterface
{
public:
	TetrisLogicSystem(GameBoard *aGameBoard);
	~TetrisLogicSystem(void);

	virtual void updateSystem(float deltaTime);

private:


	FullLineCombination *_fullLineCombination;
	SimilarTetraminosCombination *_similarTetraminosCombination;
	FillingGapInBoardSystem *_fillingGapInBoardDelegate;

};

