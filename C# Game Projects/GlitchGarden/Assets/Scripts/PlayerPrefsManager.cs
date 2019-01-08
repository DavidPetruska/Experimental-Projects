using UnityEngine;
using System.Collections;

public class PlayerPrefsManager : MonoBehaviour 
{
	const string 
		MASTER_VOLUME_KEY = "master_volume",
		DIFFICULTY_KEY = "difficulty",
		LEVEL_KEY = "level_unlocked_";

	public static void SetMasterVolume(float volume)
	{
		if (volume >= 0f && volume <= 1f)
			PlayerPrefs.SetFloat (MASTER_VOLUME_KEY, volume);
		else
			Debug.LogError ("Master Volume out of range");
	}

	public static float getMasterVolume()
	{
		return PlayerPrefs.GetFloat (MASTER_VOLUME_KEY);
	}

	public static void UnlockLevel(int level)
	{
		if (level <= Application.levelCount - 1)
			PlayerPrefs.SetInt (LEVEL_KEY + level + level.ToString (), 1); 
		else
			Debug.LogError("Trying to unlock a level that does not exist");
	}

	public static bool isLevelUnlocked(int level)
	{
		int levelValue = PlayerPrefs.GetInt (LEVEL_KEY + level.ToString ());
		bool isLevelUnlocked = levelValue == 1;
		if (level <= Application.levelCount - 1)
			return isLevelUnlocked;
		else 
		{
			Debug.LogError("The level: " + level + " is not unlocked.");
			return false;

		}
	}

	public static void SetDifficulty(float diff)
	{
		if (diff >= 1f && diff <= 3f)
			PlayerPrefs.SetFloat (DIFFICULTY_KEY, diff);
		else
			Debug.LogError ("Difficulty is out of range");
	}

	public static float getDifficulty()
	{
		return PlayerPrefs.GetFloat (DIFFICULTY_KEY);
	}


}
