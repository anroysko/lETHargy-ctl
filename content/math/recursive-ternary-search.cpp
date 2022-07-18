/**
 * Author: Yuhao Yao
 * Description: for convex function $f: \mathbb{R}^d \to \mathbb{R}$, we can approximately find the global minimum using ternary search on each coordinate recursively.
 * Usage: $d$ is the dimension; $mn, mx$ record the minimum and maximum possible value of each coordinate (the region you do ternary search); $f$ is the convex function.
 * Time: O(\log(1 / \epsilon) ^ {d} \cdot T), where $T$ is the time for evaluating the function $f$.
 */

// use T = double or long double.
template<class T> T rec_ters(int d, const vector<T> &mn, const vector<T> &mx, function<T(const vector<T>&)> f) {
	function<T(int, vector<T> &)> dfs = [&](int dep, vector<T> &p) {
		if (dep == d) return f(p);
		T l = mn[dep], r = mx[dep];
		rep(_, 1, 60) {
			T m1 = (l * 2 + r) / 3;
			T m2 = (l + r * 2) / 3;

			p[dep] = m1; T res1 = dfs(dep + 1, p);
			p[dep] = m2; T res2 = dfs(dep + 1, p);
			if (res1 < res2) r = m2;
			else l = m1;
		}
		p[dep] = (l + r) / 2;
		return dfs(dep + 1, p);
	};
	vector<T> dum(d);
	return dfs(0, dum);
}