using UnityEngine;
using System.Collections;

public class Defender : MonoBehaviour {
	private StarDisplay starDisplay;
	public int starCost;
	void Start(){
		starDisplay = GameObject.FindObjectOfType<StarDisplay> ();
	}
	public void addStars(int StarCount){
		starDisplay.addStars (StarCount);
	}
}
