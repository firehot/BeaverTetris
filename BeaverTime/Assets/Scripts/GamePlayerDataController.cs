﻿using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Collections.Generic;
using System;

public class GamePlayerDataController {

    const string playerDataFileName = "/playerData.bt";

    public bool playerExist { get; set; }
    public float gameMusicVolume { get; set; }
    public float gameSoundEffectsVolume { get; set; }
    public string playerName { get; set; }

    public int completedLevelsCount { get; set; }
    public int playerScore { get; set; }
    public int selectedLevelIndex { get; set; }

    string _dataPath;

    List<LevelSpell> _playerSpells;

    public GamePlayerDataController()
    {
        _dataPath = Application.persistentDataPath + playerDataFileName;
        loadPlayerData();
        selectedLevelIndex = 0;
    }

    void loadPlayerData()
    {

        if(File.Exists(_dataPath))
        {
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream file = File.Open(_dataPath, FileMode.Open);
            PlayerData data = formatter.Deserialize(file) as PlayerData;

            playerExist = data.playerExist;
            gameMusicVolume = data.gameMusicVolume;
            gameSoundEffectsVolume = data.gameSoundEffectsVolume;
            playerName = data.playerName;
            completedLevelsCount = data.completedLevelsCount;
            playerScore = data.playerScore;
            _playerSpells = data.playerSpells;

            if (_playerSpells == null)
            {
                _playerSpells = new List<LevelSpell>();
            }

            file.Close();
        }

    }

    public void savePlayerData()
    {
        BinaryFormatter formatter = new BinaryFormatter();
        FileStream file = File.Create(_dataPath);
        PlayerData savingData = new PlayerData();

        savingData.playerExist = playerExist;
        savingData.gameMusicVolume = gameMusicVolume;
        savingData.gameSoundEffectsVolume = gameSoundEffectsVolume;
        savingData.playerName = playerName;
        savingData.completedLevelsCount = completedLevelsCount;
        savingData.playerScore = playerScore;
        savingData.playerSpells = _playerSpells;

        formatter.Serialize(file, savingData);
        file.Close();
    }

    public void createNewPlayerWithName(string aPlayerName)
    {
        playerExist = true;
        playerName = aPlayerName;
        completedLevelsCount = 0;
        playerScore = 0;
        savePlayerData();
    }

    public void cleanPlayer()
    {
        playerExist = false;
        playerName = "";
        completedLevelsCount = 0;
        playerScore = 0;
        _playerSpells = new List<LevelSpell>();
        gameMusicVolume = 0.5f;
        gameSoundEffectsVolume = 0.5f;
        selectedLevelIndex = 0;
        savePlayerData();
    }

    public int getPlayerSpellsCount()
    {
        return _playerSpells.Count;
    }

    public void setPlayerSpell(LevelSpell aSpellData)
    {
        if (aSpellData.spellType > (getPlayerSpellsCount() - 1))
        {
            _playerSpells.Add(aSpellData);
        }
        else
        {
            _playerSpells[aSpellData.spellType] = aSpellData;
        }
    }

    public LevelSpell getPlayerSpellForIndex(int aSpellIndex)
    {
        return _playerSpells[aSpellIndex];
    }

}

[Serializable]
public class PlayerData
{
    public bool playerExist;
    public float gameMusicVolume;
    public float gameSoundEffectsVolume;
    public string playerName;
    public int completedLevelsCount;
    public int playerScore;
    public List<LevelSpell> playerSpells;

}
