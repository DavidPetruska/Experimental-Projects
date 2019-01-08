using UnityEngine;
using System.Collections;
[RequireComponent(typeof(Rigidbody2D))]
public class Attacker : MonoBehaviour {
	public float spawnDelay;
	private float CurrentWalkSpeed;
	private GameObject currentTarget;
	private Animator animator;
	// Use this for initialization
	void Start () {
		animator = GetComponent<Animator> ();
	}
	
	// Update is called once per frame
	void Update () {
		transform.Translate (Vector3.left * CurrentWalkSpeed * Time.deltaTime);
		if (!currentTarget)
			animator.SetBool ("isAttacking", false);
	}
	void OnTriggerEnter2D()	{

	}
	public void SetWalkingSpeed(float SpeedToSet){
		CurrentWalkSpeed = SpeedToSet;
	}
	public void StrikeCurrentTarget(float damageToDeal){
		if(currentTarget){
			Health health = currentTarget.GetComponent<Health> ();
			if(health)
				health.dealDamage(damageToDeal);
		}
	}
	public void Attack(GameObject obj){
		currentTarget = obj;
	}
}
