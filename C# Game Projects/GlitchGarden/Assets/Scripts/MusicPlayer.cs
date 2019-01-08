using UnityEngine;
using System.Collections;

public class MusicPlayer : MonoBehaviour 
{
	public AudioClip[] levelMusicChangeArray;
	private AudioSource audioSource;
	// Use this for initialization
	void Awake()
	{
		DontDestroyOnLoad (gameObject);

	}

	void Start()
	{
		audioSource = GetComponent<AudioSource> ();
	}

	void OnLevelWasLoaded(int level)
	{
		AudioClip levelClip = levelMusicChangeArray [level];
		if (levelClip) 
		{
			audioSource.clip = levelClip;
			audioSource.loop = true;
			audioSource.Play();
		}
	}

	public void SetVolume(float vol)
	{
		audioSource.volume = vol;
	}
}