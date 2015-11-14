using UnityEngine;
using System.Collections;

public class UIMgr : MonoBehaviour {
	private bool rightFlag = true;
	private bool leftFlag = false;

	private Transform playerTr;
	public float movSpeed = 0.5f;


	void Start(){
		playerTr = GameObject.FindWithTag ("Player").GetComponent<Transform> ();
	}

	// Button Event
	public void OnClickJumpButton(){
		Debug.Log ("Jump!");
	}

	public void OnClickLeftButton(){
		Debug.Log ("Move Left");
		if(!leftFlag){
			playerTr.Rotate (0, 180.0f, 0);
			rightFlag = false;
			leftFlag = true;
		}
		playerTr.Translate (Vector3.right * movSpeed * Time.deltaTime, Space.Self);
	}

	public void OnClickRightButton(){
		Debug.Log ("Move Right");

		if(!rightFlag){
			playerTr.Rotate (0, 180.0f, 0);
			rightFlag = true;
			leftFlag = false;
		}
		playerTr.Translate (Vector3.right * movSpeed * Time.deltaTime, Space.Self);
	}

	public void OnClickInventory(){
		Debug.Log ("Pop up Mode");
	}

	public void OnClickAngle(){

		Debug.Log ("Angle");
	}

	public void OnClickFireButton(){
		Debug.Log ("Fire!");
	}

	public void OnClickCameraButton(){
		Debug.Log ("Camera Clicked!");
	}
}
