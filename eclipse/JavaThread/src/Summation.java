
public class Summation implements Runnable{
	private int upper;
	private Sum sumValue;
	
	public Summation(int upper, Sum sumValue){
		this.upper = upper;
		this.sumValue = sumValue;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		int sum = 0;
		for(int i=0;i<=upper;i++){
			sum+= i;
			sumValue.setSum(sum);
		}
	}
	
	
}
