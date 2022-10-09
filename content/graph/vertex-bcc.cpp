/**
 * Author: Yuhao Yao
 * Date: 22-10-04
 * Description: Compute the Vertex-BiConnected Components of a graph $G = (V, E)$ (not necessarily connected). 
 *  Multiple edges and self loops are allowed.
 *  $id[i]$ records the index of bcc the edge $i$ is in.
 *  $top[u]$ records the second highest vertex (which is unique) in the bcc which vertex $u$ is in.
 * Time: O(|V| + |E|).
 * Status: tested on https://codeforces.com/gym/102900/problem/K, https://www.luogu.com.cn/problem/P4630, https://codeforces.com/contest/487/problem/E, https://www.luogu.com.cn/problem/P4606.
 */

struct VertexBCC {
	int n, bcc;
	vi id, top, fa;
	vector<pii> bf; // edges of the block-forest.
	VertexBCC(int n, const vector<pii> &es): n(n), bcc(0), id(sz(es)), top(n), fa(n, -1) {
		vvi g(n);
		rep(ind, 0, sz(es) - 1) {
			auto [x, y] = es[ind];
			g[x].push_back(ind);
			g[y].push_back(ind);
		}

		int cnt = 0;
		vi dfn(n, -1), low(n), mark(sz(es)), vsta, esta;
		auto dfs = [&](auto dfs, int now) -> void {
			low[now] = dfn[now] = cnt++;
			vsta.push_back(now);
			for (auto ind: g[now]) if (mark[ind] == 0) {
				mark[ind] = 1;
				esta.push_back(ind);
				auto [x, y] = es[ind];
				int v = now ^ x ^ y;
				if (dfn[v] == -1) {
					dfs(dfs, v);
					fa[v] = now;
					low[now] = min(low[now], low[v]);
					if (low[v] >= dfn[now]) {
						bf.emplace_back(n + bcc, now);
						while (1) {
							int z = vsta.back();
							vsta.pop_back();
							top[z] = v;
							bf.emplace_back(n + bcc, z);
							if (z == v) break;
						}
						while (1) {
							int z = esta.back();
							esta.pop_back();
							id[z] = bcc;
							if (z == ind) break;
						}
						bcc++;
					}
				} else low[now] = min(low[now], dfn[v]);
			}
		};
		rep(i, 0, n - 1) if (dfn[i] == -1) {
			dfs(dfs, i);
			top[i] = i;
		}
	}
	bool SameBcc(int x, int y) {
		if (x == fa[top[y]] || y == fa[top[x]]) return 1;
		else return top[x] == top[y];
	}
	vector<pii> getBlockForest() { return bf; }
};