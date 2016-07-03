﻿using UnityEngine;
using System.Collections;

public class AdsController : MonoBehaviour {

	public GameGlobalSettings settings;
	public FinalChanceController chanceController;
	public LevelResultsController levelResultsController;
	public string vungleID;

	bool _finalChanceAd;
	bool _simplifyGameAd;

	void Start () {
	
		if (settings.showVungleAds) 
		{
			Vungle.init("5771811c74088aef5400016b", "Test_iOS", vungleID);
		}
	}

	void Update () {
	
	}

	void OnApplicationPause(bool pauseStatus) {

		if (settings.showVungleAds) 
		{
			if (pauseStatus) {
				Vungle.onPause();
			}
			else {
				Vungle.onResume();
			}
		}
	}

	void OnEnable()
	{
		if (settings.showVungleAds) 
		{
			Vungle.onAdFinishedEvent += onAdFinishedEventVungle;
		}
	}
		
	void OnDisable()
	{
		if (settings.showVungleAds) 
		{
			Vungle.onAdFinishedEvent -= onAdFinishedEventVungle;
		}
	}

	void onAdFinishedEventVungle(AdFinishedEventArgs arg)
	{
		if(_finalChanceAd)
		{
			chanceController.getReward();
			_finalChanceAd = false;
		}

		if(_simplifyGameAd)
		{
			levelResultsController.simplifyGame();
			_simplifyGameAd = false;
		}
	}

	public bool adAvailable() {

		bool adAvailable = false;

		if(settings.showAds)
		{
			if (settings.showVungleAds) 
			{
				adAvailable = Vungle.isAdvertAvailable ();
			}
		}
			
		return adAvailable;
	}

	public void showFinalChanceAd() {

		_finalChanceAd = true;

		if (settings.showVungleAds) 
		{
			Vungle.playAd();
		}
	}

	public void showSimplifyGameAd() {

		_simplifyGameAd = true;

		if (settings.showVungleAds) 
		{
			Vungle.playAd();
		}
	}

}