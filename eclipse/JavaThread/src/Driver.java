
public class Driver {
	public static void main(String[] argv){
		// create the object to be shared
		Sum sumObject = new Sum();
		int upper = Integer.parseInt(argv[0]);
		if(argv.length>0){
			if(Integer.parseInt(argv[0])<0){
				System.err.println(argv[0]+" must be >= 0.");
			}else{		
				Thread thrd = new Thread(new Summation(upper,sumObject));
				thrd.start(); 	//thread create
				try{
					thrd.join();
					System.out.println("The sum of "+upper+" is "+sumObject.getSum());
				}catch(InterruptedException ie){}
			}
		}else{
			//System.err.println("m of "+upper+" is  "+sumObject.getSum());
		}
	}
}
