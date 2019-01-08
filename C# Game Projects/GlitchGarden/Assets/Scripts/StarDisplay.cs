using UnityEngine;
using UnityEngine.UI;
using System.Collections;
[RequireComponent(typeof(Text))]
public class StarDisplay : MonoBehaviour {
	private Text starCount;
	private int starAmount = 100;
	// Use this for initialization
	void Start () {
		starCount = GetComponent<Text>();
		starCount.text = starAmount.ToString ();
	}
	public void addStars(int starCount){
		starAmount += starCount;
		UpdateDisplay();
	}
	public bool useStar(int starCount){
		if (starAmount >= starCount) {
			starAmount -= starCount;
			UpdateDisplay ();
			return true;
		}
		return false;
	}
	private void UpdateDisplay(){
		starCount.text = starAmount.ToString();
	}
}
