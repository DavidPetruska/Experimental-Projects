using UnityEngine;
using System.Collections;

public class SpawnTower : MonoBehaviour {
	private SpawnTower[] spawnTowerArray;
	public GameObject defender;

	public static GameObject selectedUnit;
	// Use this for initialization
	void Start () {
		spawnTowerArray = GameObject.FindObjectsOfType<SpawnTower> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	void OnMouseDown(){
		foreach (SpawnTower thisOption in spawnTowerArray) {
			thisOption.GetComponent<SpriteRenderer> ().color = Color.black;
		}
		GetComponent<SpriteRenderer>().color = Color.white;
		selectedUnit = defender;
	}
}
