/**
 * Author: Yuhao Yao
 * Date: 22-09-09
 * Description: For an edge set $E$ such that each vertex has an even degree, compute Euler tour for each connected component.
 *  Note that this is a non-recursive implementation, which avoids stack size issue on some OJ and also saves memory (roughly saves 2/3 of memory) due to that.
 * Time: $O(|V| + |E|)$.
 * Status: tested on https://acm.hdu.edu.cn/showproblem.php?pid=7261, https://ac.nowcoder.com/acm/contest/4010/H.
 */

struct EulerTour {
	int n;
	vector<vi> tours;
	vi ori;

	EulerTour(int n, const vector<pii> &es, int dir = 0): n(n), ori(sz(es)) {
		vector<vi> g(n);
		int m = 0;
		for (auto [x, y]: es) {
			g[x].push_back(m);
			if (!dir) g[y].push_back(m);
			m++;
		}

		vi path, cur(n);
		vector<pii> sta;
		auto solve = [&](int st) {
			sta.emplace_back(st, -1);
			while (sz(sta)) {
				auto [now, pre] = sta.back();
				int fin = 1;
				for (int &i = cur[now]; i < sz(g[now]); ) {
					auto ind = g[now][i++];
					if (ori[ind]) continue;
					auto [x, y] = es[ind];
					ori[ind] = x == now ? 1 : -1;
					int v = now ^ x ^ y;
					sta.emplace_back(v, ind);
					fin = 0;
					break;
				}
				if (fin) {
					if (pre != -1) path.push_back(pre);
					sta.pop_back();
				}
			}
		};

		rep(i, 0, n - 1) {
			path.clear();
			solve(i);
			if (sz(path)) {
				reverse(all(path));
				tours.push_back(path);
			}
		}
	}

	vector<vi> getTours() { return tours; }

	vi getOrient() { return ori; }
};