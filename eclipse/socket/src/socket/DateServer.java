package socket;

import java.net.*;
import java.io.*;

public class DateServer {
	public static void main(String[] args){
		try{
			ServerSocket sock = new ServerSocket(20000);
			
			//연결을 listen()
			while(true){
				Socket client = sock.accept();
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				
				//Date를 소켓에 쓴다
				pout.println(new java.util.Date().toString());
				
				//소켓을 닫고 다시 시작한다.
				client.close();
			}
		}catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}
