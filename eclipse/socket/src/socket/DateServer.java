package socket;

import java.net.*;
import java.io.*;

public class DateServer {
	public static void main(String[] args){
		try{
			ServerSocket sock = new ServerSocket(20000);
			
			//������ listen()
			while(true){
				Socket client = sock.accept();
				
				PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
				
				//Date�� ���Ͽ� ����
				pout.println(new java.util.Date().toString());
				
				//������ �ݰ� �ٽ� �����Ѵ�.
				client.close();
			}
		}catch(IOException ioe){
			System.err.println(ioe);
		}
	}
}
