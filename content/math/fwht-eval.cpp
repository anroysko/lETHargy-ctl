/**
 * Author: Yuhao Yao
 * Description: Let $b = fwt(a)$. One can calculate $b_{id}$ for some index $id$ in $O(N)$ time.
 * Usage: length of $a$ should be a power of $2$.
 * Time: O(N).
 */

template<class T> T fwt_eval(const vector<T> &a, int id) {
	int N = sz(a);
	T res = 0;
	rep(i, 0, N - 1) {
		if (__builtin_popcount(i & id) & 1) res -= a[i];
		else res += a[i];
	}
	return res;
}