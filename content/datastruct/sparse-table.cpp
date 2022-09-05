/**
 * Author: Yuhao Yao
 * Date: 22-07-23
 * Description: Sparse Table.
 * Time: O(N \log N) for construction, O(1) per query.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/B, https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M.
 */

template<class T, class F = function<T(const T&, const T&)>>
class SparseTable {
	int n;
	vector<vector<T>> st;
	const F func;
public:
	SparseTable(const vector<T> &a, const F &f): n(sz(a)), func(f) {
		assert(n > 0);
		st.assign(__lg(n) + 1, vector<T>(n));
		st[0] = a;
		rep(i, 1, __lg(n)) rep(j, 0, n - (1 << i)) st[i][j] = func(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
	}

	T ask(int l, int r) {
		assert(0 <= l && l <= r && r < n);
		int k = __lg(r - l + 1);
		return func(st[k][l], st[k][r - (1 << k) + 1]);
	}
};