using UnityEngine;
using System.Collections;

public class FireCtrl : MonoBehaviour {

	// 무기 프리팹
	public GameObject projectile;
	// 무기 발사좌표
	public Transform firePos;

	// Update is called once per frame
	void Update () {
		//if (UIMgr.OnClickFireButton ()) {
		//	Fire();
		//}

		if (Input.GetMouseButtonDown (0)) {
			Fire ();
		}
	}

	void Fire(){
		// 프리팹 동적 생성
		Instantiate (projectile, firePos.position, firePos.rotation);
	}
	
}
