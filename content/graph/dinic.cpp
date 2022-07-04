/**
 * Author: Yuhao Yao
 * Description: Dinic algorithm for max flow.
 * Time: O(n^2 m) for arbitrary networks. O(m \sqrt{n}) for bipartite network. O(min{|V|^(2/3), |E|^(1/2)} |E|) for networks with only unit capacities.
 */

template<class F = int, F F_MAX = numeric_limits<F>::max()> struct Dinic {
    int n;
    struct E { int to; F cap; };
    vector<E> e;
    vector<vi> g;
    vi dis; // put it here so you can get the minimum cut easily.

    Dinic(int n): n(n), g(n) {}

    void add(int u, int v, F c) {
        g[u].push_back(sz(e)); e.push_back({v, c});
        g[v].push_back(sz(e)); e.push_back({u, 0});
    }

    F max_flow(int src, int sink) {
        vi cur;

        auto bfs = [&]() {
            dis.assign(n, -1);
            queue<int> que;
            que.push(src); dis[src]=0;
            
            while (sz(que)) {
                int now = que.front(); que.pop();
                for (auto i: g[now]) {
                    auto [v, c] = e[i];
                    if (c > 0 && dis[v] == -1) {
                        dis[v] = dis[now] + 1;
                        que.push(v);
                    }
                }
            }
            return dis[sink] != -1;
        };

        function<F(int, F)> dfs = [&](int now, F flow) {
            if (now == sink) return flow;
            F res = 0;
            for (int &id = cur[now]; id < sz(g[now]); id++) {
                int i = g[now][id];
                auto [v, c] = e[i];
                if (c > 0 && dis[v] == dis[now] + 1) {
                    F x = dfs(v, min(flow - res, c));
                    res += x;
                    e[i].cap -= x;
                    e[i ^ 1].cap += x;
                }
                if (res == flow) break;
            }
            return res;
        };
        
        F ans = 0;
        while (bfs()) {
            cur.assign(n, 0);
            ans += dfs(src, F_MAX);
        }
        return ans;
    }

    vector<bool> min_cut(int src, int sink) {
        max_flow(src, sink);
        vector<bool> res(n);
        rep(i, 0, n - 1) res[i] = (dis[i] != -1);
        return res;
    }
};