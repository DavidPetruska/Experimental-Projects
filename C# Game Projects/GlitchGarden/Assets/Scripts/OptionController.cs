using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class OptionController : MonoBehaviour 
{
	public Slider volumeSlide, difficulty;
	public LevelManager levelManager;
	private MusicPlayer musicPlayer;

	// Use this for initialization
	void Start () 
	{
		musicPlayer = GameObject.FindObjectOfType<MusicPlayer> ();
		volumeSlide.value = PlayerPrefsManager.getMasterVolume ();
		difficulty.value = PlayerPrefsManager.getDifficulty ();
	}
	
	// Update is called once per frame
	void Update () 
	{
		musicPlayer.SetVolume (volumeSlide.value);
	}
	public void SaveandExit()
	{
		PlayerPrefsManager.SetMasterVolume (volumeSlide.value);
		PlayerPrefsManager.SetDifficulty (difficulty.value);
		levelManager.LoadLevel ("01A_Start");
	}
	public void SetDefault()
	{
		volumeSlide.value = .8f;
		difficulty.value =2f;
	}
}
