using UnityEngine;
using System.Collections;

public class Spawner : MonoBehaviour {
	public GameObject[] attackerPrefabArray;
	public int spawnSpeed;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		foreach (GameObject spawningAttacker in attackerPrefabArray)
			if (isTimeToSpawn (spawningAttacker))
				Spawn (spawningAttacker);
	}

	
	void Spawn(GameObject spawningAttacker){
		GameObject spawnedAttacker = (GameObject) Instantiate (spawningAttacker);
		spawnedAttacker.transform.parent = transform;
		spawnedAttacker.transform.position = transform.position;
	}
	bool isTimeToSpawn(GameObject attacker){
		Attacker attakcer = attacker.GetComponent<Attacker>();

		float spawnRate = attakcer.spawnDelay;
		float spawnsPerSec = 1 / spawnRate;

		if (Time.deltaTime > spawnRate)
			Debug.LogWarning ("Frame rate is capping enemy spawn rates");

		float threshold = spawnsPerSec * Time.deltaTime / spawnSpeed;
		if (Random.value < threshold)
			return true;
		return false;
	}
}
