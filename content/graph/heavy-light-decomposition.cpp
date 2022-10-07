/**
 * Author: Yuhao Yao
 * Date: 22-10-08
 * Description: Heavy Light Decomposition for a tree $T$ (can be modified easily for forest).
 * Usage: $g$ should be the adjacent list of the tree $T$. $rt$ for specifying the root of the tree $T$ (default 0).
 *  $chainApply(u, v, func, val)$ and $chainAsk(u, v, func)$ are used for apply / query on the simple path from $u$ to $v$ on tree $T$. $func$ is the function you want to use to apply / query on a interval. (Say rangeApply / rangeAsk of Segment tree.)
 * Time: O(|T|) for building. O(\log N) for lca. O(\log |T| \cdot A) for chainApply / chainAsk, where $A$ is the running time of $func$ in chainApply / chainAsk.
 * Status: tested on https://codeforces.com/contest/487/problem/E.
 */

struct HLD {
	int n;
	vi fa, hson, dfn, dep, top;
	HLD(vvi &g, int rt = 0): n(sz(g)), fa(n, -1), hson(n, -1), dfn(n), dep(n, 0), top(n) {
		vi siz(n);
		auto dfs = [&](auto &dfs, int now) -> void {
			siz[now] = 1;
			int mx = 0;
			for (auto v: g[now]) if (v != fa[now]) {
				dep[v] = dep[now] + 1;
				fa[v] = now;
				dfs(dfs, v);
				siz[now] += siz[v];
				if (mx < siz[v]) {
					mx = siz[v];
					hson[now] = v;
				}
			}
		};
		dfs(dfs, rt);

		int cnt = 0;
		auto getdfn = [&](auto &dfs, int now, int sp) {
			top[now] = sp;
			dfn[now] = cnt++;
			if (hson[now] == -1) return;
			dfs(dfs, hson[now], sp);
			for (auto v: g[now]) {
				if(v != hson[now] && v != fa[now]) dfs(dfs, v, v);
			}
		};
		getdfn(getdfn, rt, rt);
	}

	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = fa[top[u]];
		}
		if (dep[u] < dep[v]) return u;
		else return v;
	}

	template<class... T>
	void chainApply(int u, int v, const function<void(int, int, T...)> &func, const T&... val) {
		int f1 = top[u], f2 = top[v];
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
			func(dfn[f1], dfn[u], val...);
			u = fa[f1]; f1 = top[u];
		}
		if (dep[u] < dep[v]) swap(u, v);
		func(dfn[v], dfn[u], val...); // change here if you want the info on edges.
	}

	template<class T>
	T chainAsk(int u, int v, const function<T(int, int)> &func) {
		int f1 = top[u], f2 = top[v];
		T ans{};
		while (f1 != f2) {
			if (dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
			ans = ans + func(dfn[f1], dfn[u]);
			u = fa[f1]; f1 = top[u];
		}
		if (dep[u] < dep[v]) swap(u, v);
		ans = ans + func(dfn[v], dfn[u]); // change here if you want the info on edges.
		return ans;
	}
};