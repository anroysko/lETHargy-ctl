/**
 * Author: Yuhao Yao
 * Date: 22-09-08
 * Description: Cartesian Tree of array $as$ (of distinct values). Node with smaller depth has smaller value. Set $gr = 1$ to have top with the greatest value.
 * Time: O(N) for construction.
 * Status: Tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M, https://codeforces.com/contest/1718/problem/D.
 */

template<class T>
auto CartesianTree(const vector<T> &as, int gr = 0) {
	int n = sz(as);
	vi ls(n, -1), rs(n, -1), sta;
	rep(i, 0, n - 1) {
		while (sz(sta) && ((as[i] < as[sta.back()]) ^ gr)) {
			ls[i] = sta.back();
			sta.pop_back();
		}
		if (sz(sta)) rs[sta.back()] = i;
		sta.push_back(i);
	}
	return make_tuple(sta[0], ls, rs);
}