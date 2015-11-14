using UnityEngine;
using System.Collections;

public class MapCollider : MonoBehaviour {

	public GameObject expEffect;
	private Transform tr;

	void OnCollisionEnter2D(Collision2D coll){
		if (coll.collider.tag == "BAZOOKA") {
			Object obj = Instantiate(expEffect,coll.transform.position,Quaternion.identity);
			Destroy (obj,0.1f);

			Collider2D colls = Physics2D.OverlapCircle(coll.transform.position,0.5f);
			if(colls.attachedRigidbody != null){
				colls.attachedRigidbody.mass = 1.0f;
				colls.attachedRigidbody.AddForceAtPosition(Vector2.up,coll.transform.position);
				Debug.Log("Ouch!");
			}
			
			// 충돌한 대상 오브젝트 삭제
			DestroyObject (coll.gameObject);
		}

	}

	IEnumerator explodeEffect(){
		Debug.Log ("BOOM!");
		// 폭발 파티클 동적 생성

		
		/*Collider[] colls = Physics2D.OverlapCircle(tr.position,3.0f);
		foreach(Collider2D coll in colls){
			if(coll.attachedRigidbody != null){
				coll.attachedRigidbody.mass = 1.0f;
				Debug.Log ("Ouch!");
			}
		}*/

		yield return null;
	}

	// Use this for initialization
	void Start () {
	}
}
