using UnityEngine;
using System.Collections;

public class Health : MonoBehaviour {
	public float health;
	public void dealDamage(float damage){
		health = health - damage;
		if (health <= 0) {
			DestroyObject();
		}
	
	}

	public void DestroyObject(){
		Destroy (gameObject);
	}
}
