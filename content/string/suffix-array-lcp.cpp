/**
 * Author: Yuhao Yao
 * Date: 22-07-24
 * Description: Suffix Array with sparse table answering lcp of suffices.
 * Usage: SA sa(s + string(1, 0)) for non-cyclic suffices.
 * Time: O(|s| \log |s|) for construction. O(1) per query.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/B, https://codeforces.com/gym/102994/problem/D, https://ac.nowcoder.com/acm/contest/33195/D.
 */

#include "suffix-array.cpp"

struct SA_lcp: SA {
	vector<vi> st;
	
	template<class T> SA_lcp(const T &s): SA(s) {
		assert(n > 1);
		st.assign(__lg(n - 1) + 1, vi(n - 1));
		st[0] = h;
		rep(i, 1, __lg(n - 1)) rep(j, 0, n - 1 - (1 << i)) {
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
	// return lcp(suff[i], suff[j])
	int lcp(int i, int j) {
		assert(i != j);
		int l = rank[i], r = rank[j];
		if (l > r) swap(l, r);
		int k = __lg(r - l);
		return min(st[k][l], st[k][r - (1 << k)]);
	}
};