/**
 * Description: Fast bipartite matching.
 * Time: O(|E| \sqrt{|V|}).
 */
struct Hopcroft {
	int n, m;
	vector<vi> g;
	vi lm, rm; // record the matched vertex for each vertex on both sides.

	// two parts: part L of size n and part R of size m.
	Hopcroft(int n, int m): n(n), m(m), g(n), lm(n, -1), rm(m, -1) {}
	void add(int i, int j) { g[i].push_back(j); } // add edge from i \in L to j in R.

	int work() {
		int ans = 0;
		while (1) {
			vi ldis(n), rdis(m); // changing to static does not speed up.
			bool ok = 0;
			vi que;
			rep(i, 0, n - 1) if (lm[i] == -1) que.push_back(i);

			rep(ind, 0, sz(que) - 1) {
				int i = que[ind];
				for (auto j : g[i]) if (rdis[j] == 0) {
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
			rep(i, 0, n - 1) if (lm[i] == -1 && find(i)) ans++;
		}
		return ans;
	}
};