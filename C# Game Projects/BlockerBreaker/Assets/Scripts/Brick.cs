using UnityEngine;
using System.Collections;

public class Brick : MonoBehaviour 
{
	public Sprite[] hitSprites;
	public static int breakableCount = 0;
	public AudioClip crack;
	public GameObject smoke;

	private int timesHit;
	private LevelManager levelManager;
	private bool isBreakable;


	// Use this for initialization
	void Start () 
	{
		isBreakable = (this.tag == "Breakable");
		if (isBreakable)
			breakableCount++;

		levelManager = GameObject.FindObjectOfType<LevelManager> ();
		timesHit = 0;
	}
	
	// Update is called once per frame
	void Update () 
	{

	}
	void OnCollisionEnter2D(Collision2D col)
	{
		AudioSource.PlayClipAtPoint (crack, transform.position, 0.25f);
		if(isBreakable)
			HandleHits ();
	}
	void LoadSprites()
	{
		int spriteHitIndex = timesHit - 1;
		if (hitSprites [spriteHitIndex])
			this.GetComponent<SpriteRenderer> ().sprite = hitSprites [spriteHitIndex];
		else
			Debug.LogError ("Not enough sprites have been entered.");
	}
	void HandleHits()
	{
		int maxHits = hitSprites.Length + 1;
		timesHit++;
		if (timesHit >= maxHits) 
		{
			breakableCount--;
			levelManager.BrickDestroyed();
			SmokePuff();
			Destroy (gameObject);
		}
		else 
		{
			LoadSprites();
		}
	}
	void SmokePuff()
	{
		GameObject smokePuff = (GameObject) Instantiate(smoke, gameObject.transform.position, Quaternion.identity);
		smokePuff.particleSystem.startColor = gameObject.GetComponent<SpriteRenderer>().color;
	}
}