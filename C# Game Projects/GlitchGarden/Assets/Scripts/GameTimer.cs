using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameTimer : MonoBehaviour {
	public float levelDuration;
	private Slider gameTimer;
	private LevelManager levelManager;
	private bool isLevelEnded = false;
	private AudioSource audioSource;
	// Use this for initialization
	void Start () {
		gameTimer = GetComponent<Slider> ();
		levelManager = FindObjectOfType<LevelManager> ();
		audioSource = GetComponent<AudioSource> ();
	}	
	// Update is called once per frame
	void Update () 
	{
		gameTimer.value = Time.timeSinceLevelLoad / levelDuration;
		if (!isLevelEnded && Time.timeSinceLevelLoad >= levelDuration) {
			print ("Leveled ended, Go Job.");
			audioSource.Play();
			Invoke ("LoadNextLevel", audioSource.clip.length);
			isLevelEnded = true;
		}
	}
	void LoadNextLevel(){	
		levelManager.LoadNextLevel ();
	}
}