using UnityEngine;
using System.Collections;

public class FirePosGizmo : MonoBehaviour {

	public float _radius = 0.05f;

	void OnDrawGizmos(){
		Gizmos.color = Color.yellow;
		Gizmos.DrawLine (transform.position,transform.position + transform.right );
	}

}
