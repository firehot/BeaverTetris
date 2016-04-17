﻿using UnityEngine;
using System.Collections.Generic;
using UnityEngine.Analytics;

public class GameAnaliticsController : MonoBehaviour {

    public string playerShop;

    void Start () {

    }
	
    public void sendPlayerPlatformData()
    {
        SmartLocalization.LanguageManager languageManager = SmartLocalization.LanguageManager.Instance;
        SmartLocalization.SmartCultureInfo deviceCulture = languageManager.GetDeviceCultureIfSupported();

        Analytics.CustomEvent("Player data", new Dictionary<string, object> {
                                                            { "Player language", deviceCulture.nativeName},
                                                            { "Player device type", SystemInfo.deviceType.ToString()},
                                                            { "Player operation system", SystemInfo.operatingSystem},
                                                            { "Shop", playerShop},
                                                                              });
    }

    public void sendAnaliticMessage(string aMessage)
    {
        Analytics.CustomEvent(aMessage, new Dictionary<string, object> { });
    }

    public void sendCreateNewPlayerMessage()
    {
        Analytics.CustomEvent("Create new player", new Dictionary<string, object> {});
    }

    public void sendCurrentGameLevel()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        Analytics.CustomEvent("Current level", new Dictionary<string, object> {
                                                            { "Current level", playerData.selectedLevelIndex}
                                                                              });
    }

    public void sendUseSpellMessage(int spellType)
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        Analytics.CustomEvent("Use spell", new Dictionary<string, object> {
                                                            { "Current level", playerData.selectedLevelIndex},
                                                            { "Spell type", spellType},
                                                                              });
    }

    public void sendWinlevelMessage()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        Analytics.CustomEvent("Win level", new Dictionary<string, object> {
                                                            { "Current level", playerData.selectedLevelIndex},
                                                            { "Level award", playerData.playerScore},
                                                                              });
    }

    public void sendLoselevelMessage()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        Analytics.CustomEvent("Lose level", new Dictionary<string, object> {
                                                            { "Current level", playerData.selectedLevelIndex},
                                                                              });
    }

    void Update () {
	
	}
}