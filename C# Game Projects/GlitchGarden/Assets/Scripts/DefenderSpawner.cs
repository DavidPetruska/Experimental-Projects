using UnityEngine;
using System.Collections;

public class DefenderSpawner : MonoBehaviour {
	public Camera camera;
	private StarDisplay starDisplay;
	// Use this for initialization
	private GameObject selectedUnitSpawner;
	void Start () {
		starDisplay = FindObjectOfType<StarDisplay> ();
		selectedUnitSpawner = GameObject.Find ("Defenders");
		if(!selectedUnitSpawner)
			selectedUnitSpawner = new GameObject("Defeneders");
	}
	void OnMouseDown(){
		if (!SpawnTower.selectedUnit)
			return;
		int defenderCost = SpawnTower.selectedUnit.GetComponent<Defender> ().starCost;
		if (starDisplay.useStar (defenderCost)) {
			GameObject defender = (GameObject)Instantiate (SpawnTower.selectedUnit, SnapToGrid (CalculateWorldPointofMouseClick ()), Quaternion.identity);
			defender.transform.parent = selectedUnitSpawner.transform;
		} else
			Debug.Log ("Not enough money to purchase defender");

	}

	Vector2 SnapToGrid(Vector2 rawPos){
		return new Vector2 (Mathf.RoundToInt(rawPos.x), Mathf.RoundToInt (rawPos.y));

	}

	Vector2 CalculateWorldPointofMouseClick(){
		float mouseX = Input.mousePosition.x;
		float mouseY = Input.mousePosition.y;
		float distanceFromCamera = 10.0f;
		Vector3 weirdTriplet = new Vector3 (mouseX, mouseY, distanceFromCamera);
		Vector2 worldPos = camera.ScreenToWorldPoint (weirdTriplet);

		return worldPos;
	}
}
