using UnityEngine;
using System.Collections;

public class SetStartVolume : MonoBehaviour {
	private MusicPlayer musicPlayer;

	// Use this for initialization
	void Start () {
		musicPlayer = GameObject.FindObjectOfType<MusicPlayer> ();
		musicPlayer.SetVolume( PlayerPrefsManager.getMasterVolume ());
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
