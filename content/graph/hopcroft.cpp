/**
 * Author: Yuhao Yao
 * Date: 22-10-12
 * Description: Fast bipartite matching for bipartite graph. You can also get a vertex cover of a bipartite graph easily.
 * Time: O(|E| \sqrt{|V|}).
 * Status: vertex cover correctness is tested on https://ac.nowcoder.com/acm/contest/885/F.
 */

struct Hopcroft {
	/// start-hash
	int L, R;
	vi lm, rm; // record the matched vertex for each vertex on both sides.
	vi ldis, rdis; // put it here so you can get vertex cover easily.

	Hopcroft(int L, int R, const vector<pii> &es): L(L), R(R), lm(L, -1), rm(R, -1) {
		vector<vi> g(L);
		for (auto [x, y]: es) g[x].push_back(y);

		while (1) {
			ldis.assign(L, -1);
			rdis.assign(R, -1);
			bool ok = 0;
			vi que;
			rep(i, 0, L - 1) if (lm[i] == -1) {
				que.push_back(i);
				ldis[i] = 0;
			}
			rep(ind, 0, sz(que) - 1) {
				int i = que[ind];
				for (auto j: g[i]) if (rdis[j] == -1) {
					rdis[j] = ldis[i] + 1;
					if (rm[j] != -1) {
						ldis[rm[j]] = rdis[j] + 1;
						que.push_back(rm[j]);
					} else ok = 1;
				}
			}

			if (ok == 0) break;
			vi vis(R); // changing to static does not speed up.

			auto find = [&](auto &dfs, int i) -> int {
				for (auto j: g[i]) if (vis[j] == 0 && rdis[j] == ldis[i] + 1) {
					vis[j] = 1;
					if (rm[j] == -1 || dfs(dfs, rm[j])) {
						lm[i] = j;
						rm[j] = i;
						return 1;
					}
				}
				return 0;
			};
			rep(i, 0, L - 1) if (lm[i] == -1) find(find, i);
		}
	} /// end-hash
	
	// returns vertices matched to left part, -1 means not matched.
	vi getMatch() { return lm; }

	pair<vi, vi> vertex_cover() { /// start-hash
		vi lvc, rvc;
		rep(i, 0, L - 1) if (ldis[i] == -1) lvc.push_back(i);
		rep(j, 0, R - 1) if (rdis[j] != -1) rvc.push_back(j);
		return {lvc, rvc};
	} /// end-hash
};
