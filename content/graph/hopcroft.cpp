/**
 * Author: Yuhao Yao
 * Description: Fast bipartite matching.
 * Time: O(|E| \sqrt{|V|}).
 * Status: vertex cover tested on https://ac.nowcoder.com/acm/contest/885/F.
 */

class Hopcroft {
	int n, m;
	vector<vi> g;
	vi lm, rm; // matched vertex for each vertex on both sides.
	vi ldis, rdis; // put them here to get vertex cover easily.
public:
	// two parts: part L of size n and part R of size m.
	Hopcroft(int n, int m): n(n), m(m), g(n), lm(n, -1), rm(m, -1) {}

	// add edge from i \in L to j in R.
	void add(int i, int j) { g[i].push_back(j); }

	vi match() { // returns lm (vertices matched to left part).
		while (1) {
			ldis.assign(n, -1);
			rdis.assign(m, -1);
			bool ok = 0;
			vi que;
			rep(i, 0, n - 1) if (lm[i] == -1) {
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

			vi vis(m); // changing to static does not speed up.

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
			rep(i, 0, n - 1) if (lm[i] == -1) find(i);
		}
		return lm;
	}

	pair<vector<bool>, vector<bool>> vertex_cover() {
		vector<bool> lvc(n), rvc(m);
		match();
		rep(i, 0, n - 1) lvc[i] = ldis[i] == -1;
		rep(j, 0, m - 1) rvc[j] = rdis[j] != -1;
		return {lvc, rvc};
	} 
};