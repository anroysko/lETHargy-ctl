/**
 * Author: Yuhao Yao
 * Description: Fast Walsh-Hadamard Transform $fwt(a) = (\sum_i (-1)^{pc(i\&0)} a_i, ..., \sum_i (-1)^{pc(i\&n-1)} a_i)$. One can use it to do xor-convolution.
 * Usage: length of $a$ should be a power of $2$.
 * Time: O(N \log N), where $N$ is the length of $a$.
 */

template<class T> void fwt(vector<T> &a, int is_inv) {
	int N = sz(a);
	for (int s = 1; s < N; s <<= 1)
		for (int i = 0; i < N; i += s << 1)
			rep(j, 0, s - 1) {
				T x = a[i + j], y = a[i + j + s];
				a[i + j] = x + y; 
				a[i + j + s] = x - y;
			}

	if (is_inv) {
		for(auto &x: a) x = x / N;
	}
}