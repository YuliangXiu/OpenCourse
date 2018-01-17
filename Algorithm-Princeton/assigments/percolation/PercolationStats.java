import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class PercolationStats {
	private int N;
	private double[] pernum;

	public PercolationStats(int n, int trials){
		if (n <= 0 || trials<=0)
			throw new IllegalArgumentException("input dim can not be less than 0!"); 
		N = n;
		pernum = new double[trials];
		for(int i=0;i<trials;i++){
			pernum[i] = 0;
		}
		for(int i=0;i<trials;i++){			
			Percolation pergrid = new Percolation(N);

			while(!pergrid.percolates()){
				int randrow = StdRandom.uniform(1,N+1);
				int randcol = StdRandom.uniform(1,N+1);
				if (pergrid.isOpen(randrow,randcol) == false)
					pergrid.open(randrow,randcol);
			}
			pernum[i] = (double)pergrid.numberOfOpenSites()/(N*N);
		}
	}
	public double mean(){
		return StdStats.mean(pernum);
	}                        
	public double stddev(){
		return StdStats.stddev(pernum);
	}                      
	public double confidenceLo(){
		return mean()-(1.96*stddev()/Math.sqrt(pernum.length));
	}                
	public double confidenceHi(){
		return mean()+(1.96*stddev()/Math.sqrt(pernum.length));
	}                 
	public static void main(String[] args){
		while (!StdIn.isEmpty()) {
            int N = StdIn.readInt();
            int T = StdIn.readInt();
			PercolationStats perstats = new PercolationStats(N,T);
			StdOut.println("mean                    = "+perstats.mean());
			StdOut.println("stddev                  = "+perstats.stddev());
			StdOut.println("95% confidence interval = ["+perstats.confidenceLo()+", "+perstats.confidenceHi()+"]");
		} 
	}      
}
