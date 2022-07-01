/**
 * Author: Yuhao Yao
 * Description: Centroid Decomposition.
 * Time: O(N \log N).
 * Status: need more tests.
 */
struct CentroidDecomposition {
	// anc[i]: ancestors of vertex i in centroid tree, including itself.
	// dis[i]: distances from vertex i to ancestors of vertex i in centroid tree, not necessarily monotone.
	int n;
	vector<vi> anc, cdis;

	CentroidDecomposition(vvi &g): n(sz(g)), anc(n), cdis(n) {
		vi siz(n);
		vector<bool> vis(n);
		function<void(int, int)> solve = [&](int _, int tot) {
			int mn = inf, cent = -1;
			function<void(int, int)> getcent = [&](int now, int fa) {
				siz[now] = 1;
				int mx = 0;
				for (auto v: g[now]) if (v != fa && vis[v] == 0) {
					getcent(v, now);
					siz[now] += siz[v];
					mx = max(mx, siz[v]);
				}
				mx = max(mx, tot - siz[now]);
				if (mn > mx) mn = mx, cent = now;
			};
			getcent(_, -1); vis[cent] = 1; 

			function<void(int, int, int)> dfs = [&](int now, int fa, int dep) {
				anc[now].pb(cent);
				cdis[now].pb(dep);
				for (auto v: g[now]) if (v != fa && vis[v] == 0) dfs(v, now, dep + 1);
			};
			dfs(cent, -1, 0);
			// start your work here or inside the function dfs.

			for (auto v: g[cent]) if (vis[v] == 0) solve(v, siz[v] < siz[cent] ? siz[v] : tot - siz[cent]);
		};

		solve(0, n);
	}
};