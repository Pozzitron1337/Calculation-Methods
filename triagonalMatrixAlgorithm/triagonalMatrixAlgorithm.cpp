	/**
	 * 
	 * 		|c_0 b_0  0   0   0  0 .....  0|   |   x_0 	 |	 |   d_0   |
	 * 		|a_1 c_1 b_1  0   0  0 .....  0|   |   x_1 	 |	 |   d_1   |
	 * 		| 0  a_2 c_2 b_2  0  0 .....  0|   |   x_2 	 |	 |   d_2   |
	 *  A = | 0   0  a_3 c_3 b_3 0 .....  0| * |   x_3 	 | = |   d_3   |
	 * 		|..............................|   |   ... 	 |	 |   ...   |
	 * 		| 0 ...  a_(n-2) c(n-2) b_(n-2)|   | x_(n-2) |	 | d_(n-2) |
	 * 		| 0   0  ...  0 a_(n-1) c_(n-1)|   | x_(n-1) |	 | d_(n-1) |
	 * 
	 * works when a[0]=0 and b[n-1]=0
	 * 
	 * n - dimension of matrix
	 * b - upper diagonal ([0;n-2])
	 * c - main diagonal of matrix A ([0;n-1])
	 * a - under diagonal ([1;n-1])
	 * d - column(right side)
	 * x - solution, array x will contain the answer
	 */
void triagonalMatrixAlgorithm (int n, double *a, double *c, double *b, double *d, double *x)
{
	double t;
	for (int i = 1; i < n; i++){
		t = a[i]/c[i-1];
        d[i] = d[i] - t*d[i-1];
		c[i] = c[i] - t*b[i-1];
	}
	x[n-1] = d[n-1]/c[n-1];
	for (int i = n - 2; i >= 0; i--){
		x[i]=(d[i]-b[i]*x[i+1])/c[i];
    }
}