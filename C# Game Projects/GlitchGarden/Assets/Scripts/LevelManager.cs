using UnityEngine;
using System.Collections;

public class LevelManager : MonoBehaviour 
{
	public float autoLoadNextLevel;

	void Start()
	{
		if (autoLoadNextLevel < 0)
			Debug.LogError ("autoLoadNextLevel needs to be a positive integer to load the next level.");
		else if (autoLoadNextLevel == 0)
			return;
		else
			Invoke ("LoadNextLevel", autoLoadNextLevel);
	}
	public void LoadLevel(string name)
	{
		Application.LoadLevel (name);
	}
	public void QuitRequest()
	{
		Application.Quit ();
	}
	public void LoadNextLevel()
	{
		Application.LoadLevel (Application.loadedLevel + 1);
	}
}