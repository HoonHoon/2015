using UnityEngine;
using System.Collections;

public class PlayerCtrl : MonoBehaviour {

	//public delegate void UIHandler();
	//public static event UIHandler leftMove;
	//public static event UIHandler rightMove;
	private float h = 0.0f;
	private float v = 0;
	public int hp = 100;
	public float movSpeed = 5.0f;
	public Transform tr;
	public Transform firePos;
	public Rigidbody2D rb;
	// Use this for initialization
	void Start () {
		tr = transform.GetComponent<Transform> ();
		firePos = transform.FindChild("FirePos");
	}

	/*void OnCollisionEnter2D(Collision2D coll){
		if (coll.collider.tag == "BAZOOKA") {
			// 충돌된 위치 저장 
			Vector3 collPos = transform.position;
			Debug.Log ("!!"+collPos);
			Debug.Log ("Player"+tr.position);
		}
	}*/

	// Update is called once per frame
	void Update () {
		//h = AndroidInput._;
		h = Input.GetAxis ("Horizontal");
		v = Input.GetAxis ("Vertical");
		// 좌 우 이동
		tr.Translate (Vector2.right * h * movSpeed * Time.deltaTime, Space.Self);
		firePos.Rotate (0, 0, v);

		// 상 하 각조절
		rb = GetComponent<Rigidbody2D> ();
		//Debug.Log (h);
		if (Input.GetKeyDown (KeyCode.X)) {
			rb.AddForce (transform.up * 500);
		}

	}
}
