/**
 * Author: Yuhao Yao
 * Description: Fast Subtset Transform. Also known as fast zeta transform.
 * Usage: length of $a$ should be a power of $2$.
 * Time: O(N \log N), where $N$ is the length of $a$.
 */

template<class T> void fst(vector<T> &a) {
	int N = sz(a);
	for (int s = 1; s < N; s <<= 1) {
		rep(i, 0, N - 1) if (i & s) a[i] += a[i ^ s];
	}
}

template<class T> void ifst(vector<T> &a) {
	int N = sz(a);
	for (int s = 1; s < N; s <<= 1) {
		for (int i = N - 1; i >= 0; --i) if (i & s) a[i] -= a[i ^ s];
	}
}