/**
 * Author: Yuhao Yao
 * Description: heavy light decomposition.
 * Time: O(N) for building. O(\log N) for lca. O(\log N \cdot T) for add / ask. $T$ is the running time of func in add / ask.
 */

struct HLD {
	int n;
	vi par, hson, dfn, dep, top;
	HLD(vvi &g, int rt = 0): n(sz(g)), par(n, -1), hson(n, -1), dfn(n), dep(n, 0), top(n) {
		vi siz(n);
		function<void(int, int)> dfs = [&](int now, int fa) {
			siz[now] = 1;
			int mx = 0;
			for (auto v: g[now]) if (v != fa) {
				dep[v] = dep[now] + 1;
				par[v] = now;
				dfs(v, now);
				siz[now] += siz[v];
				if (mx < siz[v]) mx = siz[v], hson[now] = v;
			}
		};
		dfs(rt, -1);

		int cnt = 0;
		function<void(int, int)> getdfn = [&](int now, int sp) {
			top[now] = sp;
			dfn[now] = cnt++;
			if (hson[now] == -1) return;
			getdfn(hson[now], sp);
			for (auto v: g[now]) if(v != hson[now] && v != par[now]) getdfn(v, v);
		};
		getdfn(rt, rt);
	}

	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = par[top[u]];
		}
		if (dep[u] < dep[v]) return u;
		else return v;
	}

	// the following function is for info on edges.
	template<class T> void add(const function<void(int, int, T)> &func, int u, int v, const T &val) {
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
			func(dfn[f1], dfn[u], val);
			u = par[f1]; f1 = top[u];
		}
		if (dep[u] < dep[v]) swap(u, v);
		if (u != v) func(dfn[hson[v]], dfn[u], val); // change here if you want the info on vertices.
	}

	// the following function is for info on edges.
	template<class T> T ask(const function<T(int, int)> &func, int u, int v) {
		int f1 = top[u], f2 = top[v];
		T ans = 0;
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
			ans += func(dfn[f1], dfn[u]);
			u = par[f1]; f1 = top[u];
		}
		if (dep[u] < dep[v]) swap(u, v);
		if (u != v) ans += func(dfn[hson[v]], dfn[u]); // change here if you want the info on vertices.
		return ans;
	}
};