/**
 * Author: Yuhao Yao
 * Date: 22-08-25
 * Description: Dinic algorithm for max flow.
 * Time: O(n^2 m) for arbitrary networks. O(m \sqrt{n}) for bipartite/unit network. O(min{|V|^(2/3), |E|^(1/2)} |E|) for networks with only unit capacities.
 * Usage: Always run $MaxFlow(src, sink)$ for some $src$ and $sink$ first. Then you can run $getMinCut$ to obtain a Minimum Cut. Note that in the returned cut, vertices in the same part as $src$ are marked with $1$.
 * Status: tested on https://codeforces.com/gym/103861/problem/H. Seems to be fast enough now.
 *  getDirFlow() and getUndirFlow() are not tested yet.
 */

template<class Cap = int, Cap F_MAX = numeric_limits<Cap>::max()> struct Dinic {
	/// start-hash
	int n;
	struct E { int to; Cap a; }; // Endpoint & Admissible flow.
	vector<E> es;
	vector<vi> g;
	vi dis; // Put it here to get the minimum cut easily.

	Dinic(int n): n(n), g(n) {}

	void addEdge(int u, int v, Cap c, bool dir = 1) {
		g[u].push_back(sz(es)); es.push_back({v, c});
		g[v].push_back(sz(es)); es.push_back({u, dir ? 0 : c});
	}

	Cap MaxFlow(int src, int sink) {
		auto revbfs = [&]() {
			dis.assign(n, -1);
			dis[sink] = 0;
			vi que{sink};
			
			rep(ind, 0, sz(que) - 1) {
				int now = que[ind];
				for (auto i: g[now]) {
					auto v = es[i].to;
					if (es[i ^ 1].a > 0 && dis[v] == -1) {
						dis[v] = dis[now] + 1;
						que.push_back(v);
						if (v == src) return 1;
					}
				}
			}
			return 0;
		};

		vi cur;
		auto dfs = [&](auto dfs, int now, Cap flow) {
			if (now == sink) return flow;
			Cap res = 0;
			for (int &id = cur[now]; id < sz(g[now]); id++) {
				int i = g[now][id];
				auto [v, c] = es[i];
				if (c > 0 && dis[v] == dis[now] - 1) {
					Cap x = dfs(dfs, v, min(flow - res, c));
					res += x;
					es[i].a -= x;
					es[i ^ 1].a += x;
				}
				if (res == flow) break;
			}
			return res;
		};
		
		Cap ans = 0;
		while (revbfs()) {
			cur.assign(n, 0);
			ans += dfs(dfs, src, F_MAX);
		}
		return ans;
	} /// end-hash
	// res[i] = 1 <-> vertex i is in the same part as src.
	vi getMinCut() { /// start-hash
		vi res(n);
		rep(i, 0, n - 1) res[i] = (dis[i] == -1);
		return res;
	} /// end-hash
	// Gives flow on edge assuming it is directed/undirected. Undirected flow is signed.
	Cap getDirFlow(int i) { return es[i * 2 + 1].a; }
	Cap getUndirFlow(int i) { return (es[i * 2 + 1].a - es[i * 2].a) / 2; }
};