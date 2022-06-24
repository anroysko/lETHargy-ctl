/**
 * Description: 2SAT solve, returns if a 2SAT problem is satisfiable. If yes, it also gives an assignment.
 * Usage: For example, if you want to add clause (not x) or (y), just call addclause(x, 0, y, 1);
 * Time: O(|V| + |C|)
 */
struct TwoSat {
	int n;
	vector<vi> e;
	vector<bool> ans;
	TwoSat(int n): n(n), e(n * 2), ans(n) {}

	void addclause(int x, int f, int y, int g) {
		e[x * 2 + !f].pb(y * 2 + g);
		e[y * 2 + !g].pb(x * 2 + f);
	}

	bool solve() {
		vi id(n * 2, -1), dfn(n * 2, -1), low(n * 2, -1), sta;
		int cnt = 0, scc = 0;

		function<void(int)> dfs = [&](int now) {
			dfn[now] = low[now] = cnt++;
			sta.pb(now);
			for (auto v: e[now]) {
				if (dfn[v] == -1) {
					dfs(v);
					low[now] = min(low[now], low[v]);
				}
				else if (id[v] == -1) low[now] = min(low[now], dfn[v]);
			}
			if (low[now] == dfn[now])
			{
				while (sta.back() != now) {
					id[sta.back()] = scc;
					sta.pop_back();
				}
				id[sta.back()] = scc;
				sta.pop_back();
				scc++;
			}
		};

		rep(i, 0, n * 2 - 1) if (dfn[i] == -1) dfs(i);
		rep(i, 0, n - 1)
		{
			if (id[i * 2] == id[i * 2 + 1]) return 0;
			ans[i] = id[i * 2] > id[i * 2 + 1];
		}
		return 1;
	}

	void getass() { return ans; }
};