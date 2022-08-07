/**
 * Author: Yuhao Yao
 * Date: 22-08-07
 * Description: Fast maximum matching for bipartite graph $G = (V, E)$ where $V = L \cup R$. You can also get a vertex cover of a bipartite graph easily.
 * Usage: add(i, j) to add an edge from $i \in L$ to $j \in R$. call match() to get the maximum matching.
 * Time: O(|E| \sqrt{|V|}).
 * Status: Vertex cover is tested on https://ac.nowcoder.com/acm/contest/885/F.
 */

struct Hopcroft {
	/// start-hash
	int L, R;
	vector<vi> g;
	vi lm, rm; // matched vertex for each vertex on both sides.
	vi ldis, rdis; // put them here to get vertex cover easily.

	Hopcroft(int L, int R): L(L), R(R), g(L), lm(L, -1), rm(R, -1) {}

	void add(int i, int j) { g[i].push_back(j); }

	vi match() { // returns lm (vertices matched to left part).
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
				for (auto j : g[i]) if (rdis[j] == -1) {
					rdis[j] = ldis[i] + 1;
					if (rm[j] != -1) {
						ldis[rm[j]] = rdis[j] + 1;
						que.push_back(rm[j]);
					}
					else ok = 1;
				}
			}
			if (ok == 0) break;

			vi vis(R); // changing to static does not speed up.

			function<int(int)> find = [&](int i) {
				for (auto j: g[i]) if (vis[j] == 0 && rdis[j] == ldis[i] + 1) {
					vis[j] = 1;
					if (rm[j] == -1 || find(rm[j])) {
						lm[i] = j;
						rm[j] = i;
						return 1;
					}
				}
				return 0;
			};
			rep(i, 0, L - 1) if (lm[i] == -1) find(i);
		}
		return lm;
	} /// end-hash

	/// start-hash
	pair<vector<bool>, vector<bool>> vertex_cover() {
		vector<bool> lvc(L), rvc(R);
		match();
		rep(i, 0, L - 1) lvc[i] = (ldis[i] == -1);
		rep(j, 0, R - 1) rvc[j] = (rdis[j] != -1);
		return {lvc, rvc};
	} /// end-hash
};
