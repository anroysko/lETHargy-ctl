/** 
 * Author: Yuhao Yao
 * Description: finds minimum weighted perfect matching of a bipartite graph. There should be sanme number of vertices on both sides.
 * Usage: w[i][j] is the weight of the edge from i'th vertex on the left to j'th vertex on the right.
 * Time: O(|V| ^ 3)
 */
template<class T = ll, T INF = numeric_limits<T>::max()>
vector<pii> Hungarian(const vector<vector<T>> &w) {
	int n = sz(w);
	vector<T> lp(n), rp(n, 0); // left & right potential
	vi lm(n, -1), rm(n, -1); // left & right match

	rep(i, 0, n - 1) lp[i] = *min_element(all(w[i]));

	auto step = [&](int src) {
		vi que{src}, pre(n, - 1); // bfs que & back pointers
		vector<T> sa(n, INF); // slack array; Min slack from node in que

		auto extend = [&](int j) {
			if (sa[j] == 0) {
				if (rm[j] == -1) {
					while(j != -1) { // Augment the path
						int i = pre[j];
						rm[j] = i;
						swap(lm[i], j);
					}
					return 1;
				}
				else que.push_back(rm[j]);
			}
			return 0;
		};

		rep(ind, 0, n - 1) { // BFS to new nodes
			int i = que[ind];
			rep(j, 0, n - 1) {
				if (j == lm[i]) continue;
				T off = w[i][j] - lp[i] - rp[j]; // Slack in edge
				if (sa[j] > off) {
					sa[j] = off;
					pre[j] = i;
					if (extend(j)) return;
				}
			}
			if (ind == sz(que) - 1) { // Update potentials
				T d = INF;
				rep(j, 0, n - 1) if (sa[j]) d = min(d, sa[j]);
				
				bool found = 0;
				for (auto i: que) lp[i] += d;
				rep(j, 0, n - 1) {
					if (sa[j]) {
						sa[j] -= d;
						if (!found) found |= extend(j);
					} else rp[j] -= d;
				}
				if (found) return;
			}
		}
	};

	rep(i, 0, n - 1) step(i);
	
	vector<pii> res;
	rep(i, 0, n - 1) res.emplace_back(i, lm[i]);
	return res;
}