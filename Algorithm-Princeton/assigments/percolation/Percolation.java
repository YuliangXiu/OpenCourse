import edu.princeton.cs.algs4.WeightedQuickUnionUF;


public class Percolation {
	private WeightedQuickUnionUF grid;
	private WeightedQuickUnionUF exgrid;
	private int N;
	private boolean[] states; 

	public Percolation(int n){
		if (n <= 0)
			throw new IllegalArgumentException("input dim can not be less than 0!"); 
		N = n;
		grid = new WeightedQuickUnionUF(N*N+2);
		exgrid = new WeightedQuickUnionUF(N*N+1);

		states = new boolean[N*N+2];
		states[0] = true;
		states[N*N+1] = true;
		for(int i=1;i<=N*N;i++){
			states[i] = false;
		}
	}
	private int xy2index(int row, int col){
		if (legal(row,col) == false)
			throw new IndexOutOfBoundsException("row col numbers is wrong!");
		else
			return (row-1)*N+col;
	}

	private boolean legal(int row, int col){
		return (row>=1 & row<=N & col>=1 & col<=N);
	}

	public void open(int row, int col){
		if (legal(row,col) == false)
			throw new IndexOutOfBoundsException("row col numbers is wrong!");
		
		if (isOpen(row,col) == false & legal(row,col)){
			states[xy2index(row,col)] = true;
			
			if(row == 1){
				grid.union(0,xy2index(row,col));
				exgrid.union(0,xy2index(row,col));
			}
			if(row == N)
				grid.union(xy2index(row,col),N*N+1);

			if (legal(row,col-1) == true){
				if (states[xy2index(row,col-1)] == true){
					grid.union(xy2index(row,col-1),xy2index(row,col));
					exgrid.union(xy2index(row,col-1),xy2index(row,col));
				}
			}
			if (legal(row,col+1) == true){
				if (states[xy2index(row,col+1)] == true){
					grid.union(xy2index(row,col+1),xy2index(row,col));
					exgrid.union(xy2index(row,col+1),xy2index(row,col));
				}
			}	
			if (legal(row-1,col) == true){
				if (states[xy2index(row-1,col)] == true){
					grid.union(xy2index(row-1,col),xy2index(row,col));	
					exgrid.union(xy2index(row-1,col),xy2index(row,col));	
				}
			}
			if (legal(row+1,col) == true){
				if (states[xy2index(row+1,col)] == true){
					grid.union(xy2index(row+1,col),xy2index(row,col));	
					exgrid.union(xy2index(row+1,col),xy2index(row,col));	
				}
			}
		}
	}
	
	public boolean isOpen(int row, int col){
		if (legal(row,col) == false)
			throw new IndexOutOfBoundsException("row col numbers is wrong!");
		else
			return states[xy2index(row,col)];
	}
	public boolean isFull(int row, int col){
		if (legal(row,col) == false)
			throw new IndexOutOfBoundsException("row col numbers is wrong!");
		else
			return exgrid.connected(xy2index(row,col),0);
	}
	public int numberOfOpenSites(){
		int count = 0;
		for(int i=1;i<=N*N;i++)
		{
			if (states[i] == true)
				count += 1;
		}
		return count;
	}
	public boolean percolates(){
		return grid.connected(0,N*N+1);
	}
}
