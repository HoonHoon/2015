using UnityEngine;
using System.Collections;

public class BazookaCtrl : MonoBehaviour {

	public int damage = 20;
	public float speed = 100.0f;

	// 폭발효과 파티클 연결 변수
	public GameObject expEffect;

	public Rigidbody2D rb;
	public Vector3 firePos = Vector3.zero;
	public Vector3 playerPos = Vector3.zero;
	
	// Use this for initialization
	void Start () {
		// 발사 초기값
		rb = GetComponent<Rigidbody2D> ();
		rb.AddForce (transform.right * speed);
		
		// 총알 생성위치 = FirePos
		firePos = transform.position;

	}

	void OnCollisionEnter2D(Collision2D coll){

		// 충돌된 위치 저장 
		Vector3 collPos = transform.position;

		// 충돌된 위치에서 이펙트 프리팹 생성 
		Object obj = Instantiate(expEffect,collPos,Quaternion.identity);
		// 0.1초 후 이펙트 제거
		Destroy (obj,0.1f);

		// 반경 1.0f 안에 있는 collider2d 추출 
		Collider2D[] colls = Physics2D.OverlapCircleAll (collPos, 1.0f);
		foreach (Collider2D findcoll in colls) {
			// 태그가 player일 경우 
			if(findcoll.gameObject.tag == "Player"){
				playerPos = findcoll.gameObject.transform.position;
				Debug.Log ("!!"+findcoll.gameObject.transform.position);
				Debug.Log ("collPos = "+collPos);
				// 해당 방향으로 밀려난다
				findcoll.attachedRigidbody.mass = 0.5f;
				findcoll.attachedRigidbody.AddForce((playerPos - collPos)*1000.0f);
			}
		}
		// 총알 제거
		DestroyObject (gameObject);
	}

	// Update is called once per frame
	void Update () {
	
	}
}
