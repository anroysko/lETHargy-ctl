/**
 * Author: Yuhao Yao
 * Date: 22-09-17
 * Description: Compute the Vertex-BiConnected Components of a \textbf{connected} graph. 
 *  Multiple edges and self loops are allowed.
 *  $id[eid]$ records the index of bcc the edge $eid$ is in.
 *  $top[u]$ records the second highest vertex (which is unique) in the bcc which vertex $u$ is in.
 *  If the graph is not connected then only the component which $st$ is in is considered.
 * Time: O(|E|).
 * Status: tested on https://codeforces.com/gym/102900/problem/K, https://official.contest.yandex.com/contest/26874/problems/K/.
 */
struct VertexBCC {
	int bcc;
	vi dfn, low, top, id, fa;
	VertexBCC(int n, const vector<pii> &es, int st = 0): bcc(0), dfn(n, -1), low(n), top(n, -1), id(sz(es)), fa(n, -1) {
		vi mark(sz(es)), sta;
		int cnt = 0;
		vvi g(n);
		rep(ind, 0, sz(es) - 1) {
			auto [x, y] = es[ind];
			g[x].push_back(ind);
			g[y].push_back(ind);
		}
		auto dfs = [&](auto dfs, int now) -> void {
			low[now] = dfn[now] = cnt++;
			for (auto ind: g[now]) if (mark[ind] == 0) {
				mark[ind] = 1;
				int oldsz = sz(sta);
				sta.push_back(ind);
				auto [x, y] = es[ind];
				int v = now ^ x ^ y;
				if (dfn[v] == -1) {
					dfs(dfs, v);
					fa[v] = now;
					low[now] = min(low[now], low[v]);
					if (low[v] >= dfn[now]) {
						while (sz(sta) > oldsz) {
							id[sta.back()] = bcc;
							auto [a, b] = es[sta.back()];
							top[a] = top[b] = v;
							sta.pop_back();
						}
						bcc++;
					}
				} else low[now] = min(low[now], dfn[v]);
			}
		};
		dfs(dfs, st);
		top[st] = st;
	}
	bool SameBcc(int x, int y) {
		assert(dfn[x] != -1 && dfn[y] != -1);
		if (x == fa[top[y]] || y == fa[top[x]]) return 1;
		else return top[x] == top[y];
	}
};