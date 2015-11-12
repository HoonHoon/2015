import java.sql.*;

import oracle.jdbc.driver.OracleDriver;

public class Test {

	
	public static void main(String[] args) {
		Connection connect = null;
		System.out.println("Hello!\n");
		Driver driver = new OracleDriver();
		String url = "jdbc:oracle:thin:@localhost:1521:orcl";
		String user = "loginserver";
		String password = "loginserver";
		String sql = "SELECT * FROM USERLIST";
		// TODO Auto-generated method stub
		try{
			DriverManager.registerDriver(driver);
			connect = DriverManager.getConnection(url, user, password);
			Statement stmt = connect.createStatement();
			//stmt.executeQuery(arg0)	// DDL
			ResultSet rs = stmt.executeQuery(sql);
			while(rs.next()){
				int userno = rs.getInt(1);
				String id = rs.getString(2);
				String pw = rs.getString(3);
				System.out.println(userno + "\t" + id + "\t" + pw + "\n");
			}
		}catch(Exception e){
			e.printStackTrace();
		}finally{
			try{
				connect.close();
			}catch(SQLException e){
				e.printStackTrace();
			}
		}
	}

}
