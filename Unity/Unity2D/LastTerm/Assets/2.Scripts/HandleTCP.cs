using UnityEngine;
using System.Collections;
using System.Net.Sockets;
using System.Net;
using System.Threading;
using System.IO;

public class HandleTCP : MonoBehaviour {

	// 서버 소켓
	private Socket 	servSock = null;
	// 클라이언트 소켓
	private Socket 	clntSock = null;
	// 스레드 생성
	protected Thread thread = null;

	// send() recv() 단위는 packet
	//private MemoryStream buffer;

	public void ActiveServer(){
		StartServer (20000, 4);
	}

	public void ConnectServer(){
		Connect ("127.0.0.1", 20000);
	}

	// 서버 가동
	public bool StartServer(int port, int MAXPENDING){
		Debug.Log ("Server Start!");
		try{
			servSock = new Socket (AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			servSock.Bind (new IPEndPoint (IPAddress.Any, port));
			servSock.Listen (MAXPENDING);
		}catch {
			Debug.Log("StartServer fail");
			return false;
		}

		return clientAccept ();

	}

	public bool clientAccept(){
		while (true){
			Debug.Log("Waiting Accept...");

			// Polling
			if(servSock != null && servSock.Poll (0,SelectMode.SelectRead)){
				clntSock = servSock.Accept();
			}

			Debug.Log("Client Connected!");
		}
	}

	// 클라이언트 연결
	public bool Connect(string address, int port)
	{
		Debug.Log("TCP connect() called.");

		try {
            // 서버소켓에 연결
			clntSock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
			clntSock.Connect(address, port);
		}
		catch {
		    clntSock = null;
		}       
        Debug.Log("Client Connected!");
		return false;
	}

	// 송신처리.
	public int Send(byte[] data, int size)
	{
		clntSock.Send (data);
	
		return size;
	}
	
	// 수신처리.
	public int Receive(ref byte[] buffer, int size)
	{
		clntSock.Receive (buffer);
		
		return size;
	}


	public void OnClickStartBtn(){
		Debug.Log ("Click Button");
		Destroy (this);
		Application.LoadLevel ("UIMain");
		Application.LoadLevelAdditive ("scGame");

	}
	

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
