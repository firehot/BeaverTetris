﻿using UnityEngine;
using System.Collections;

public class WinGameConditionsController : MonoBehaviour {

    public GameObject[] winConditions;
    //public GameSpeedController gameSpeedController;
    public LevelResultsController resultController;

    GameObject _currentWinCondition;
    GameBoard _gameBoard;


    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        
        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        int winConditionIndex = level.winConditionType;

        _currentWinCondition = winConditions[winConditionIndex];
        _currentWinCondition.SetActive(true);
    }
	
	void Update () {
	
	}

    public void updateWithGameTime()
    {

        if (_gameBoard.gameBoardLocked == false)
        {
            IWinCondition winCondition = _currentWinCondition.GetComponent<IWinCondition>();
            if (winCondition.checkWinCondition())
            {
                resultController.winLevel();
                //gameSpeedController.stopGame = true;
            }
            else
            {
                checkLoseGameCondition();
            }
        }

    }

    void checkLoseGameCondition()
    {
        if(blockExistOnFinalLine())
        {
            resultController.loseLevel();
            //gameSpeedController.stopGame = true;
        }
    }

    bool blockExistOnFinalLine()
    {
        bool blockExist = false;

        for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, _gameBoard.getBoardHeight() - 1);
            if(block)
            {
                blockExist = true;
                break;
            }
        }

        return blockExist;
    }

}
