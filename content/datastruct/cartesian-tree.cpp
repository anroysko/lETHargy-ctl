/**
 * Author: Yuhao Yao
 * Date: 22-09-06
 * Description: Cartesian Tree. Node with smaller depth has smaller value. Smaller is defined by comparison function $cmp$.
 * Usage: $cmp$ is in the same form as the comparison function you use for std function $sort$.
 * Time: O(N) for construction.
 * Status: Tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M.
 */

struct CartesianTree {
	int n, rt;
	vi ls, rs;

	template<class T, class F = function<bool(const T&, const T&)>>
	CartesianTree(const vector<T> &as, F cmp): n(sz(as)), ls(n, -1), rs(n, - 1) {
		vi sta;
		rep(i, 0, n - 1) {
			int siz = sz(sta);
			while (siz > 0 && cmp(as[i], as[sta[siz - 1]])) siz--;
			if (siz > 0) rs[sta[siz - 1]] = i;
			if (siz < sz(sta)) ls[i] = sta[siz];
			sta.resize(siz);
			sta.push_back(i);
		}
		rt = sta[0];
	}
};