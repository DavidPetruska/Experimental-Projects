using UnityEngine;
using System.Collections;

public class Shooter : MonoBehaviour {
	public GameObject projectile, gun;
	private GameObject projectileParent;
	private Animator animator;
	private Spawner laneSpawner;
	void Start(){
		animator = GetComponent<Animator> ();
		projectileParent = GameObject.Find ("Projectiles");
		if(!projectileParent)
			projectileParent = new GameObject("Projectiles");
		setMyLanespawner ();
	}
	void Update(){
		if (enemyDetected ()) {
			animator.SetBool("isAttacking", true);
		}
		else
			animator.SetBool("isAttacking", false);

	}
	void setMyLanespawner(){
		foreach(Spawner spawners in GameObject.FindObjectsOfType<Spawner>()){
			if(spawners.transform.position.y == transform.position.y){
				laneSpawner = spawners;
				return;
			}

		}
		Debug.LogError (name + "cant find spawner");
	}
	bool enemyDetected(){
		if (laneSpawner.transform.childCount <= 0) {
			return false;
		}
		foreach (Transform child in laneSpawner.transform) {
			if(child.transform.position.x > transform.position.x)
				return true;
			else return false;
		}
		return false;
	}
	private void Fire(){
		GameObject newProjectile = Instantiate (projectile) as GameObject;
		newProjectile.transform.parent = projectileParent.transform;
		newProjectile.transform.position = gun.transform.position;
	}
}
