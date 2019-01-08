using UnityEngine;
using System.Collections;

public class LoseCollider : MonoBehaviour {
	public int loseHealth;
	private LevelManager levelManager;
	// Use this for initialization
	void Start () {
		levelManager = GameObject.FindObjectOfType<LevelManager> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	void OnTriggerEnter2D(){
		if (loseHealth > 0)
			loseHealth --;
		if (loseHealth <= 0)
			levelManager.LoadLevel ("03B_Lose");
	}
}
