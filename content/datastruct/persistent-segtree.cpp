/**
 * Author: Yuhao Yao
 * Date: 22-10-11
 * Description: Persistent Segment Tree. Point apply and thus no lazy propogation.
 * Usage: Always define a global apply function to tell segment tree how you apply modification. 
 *  Combine is set as plus so if you just let $T$ be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log N) per operation.
 * Status: tested on https://codeforces.com/contest/1479/problem/D, https://www.luogu.com.cn/problem/P7361, https://www.luogu.com.cn/problem/P4094.
 */
template<class Info> class PersistSegtree {
	/// start-hash
	struct node { Info info; int ls, rs; };
	int n;
	vector<node> t;
public:
	// node 0 is left as virtual empty node.
	PersistSegtree(int n, int q): n(n), t(1) {
		assert(n > 0);
		t.reserve(q * (__lg(n) + 2) + 1);
	}

	// pointApply returns the id of new root.
	template<class... T>
	int pointApply(int rt, int pos, const T&... val) {
		auto dfs = [&](auto &dfs, int &i, int l, int r) {
			t.push_back(t[i]);
			i = sz(t) - 1;
			::apply(t[i].info, val...);

			if (l == r) return;
			int mid = (l + r) >> 1;
			if (pos <= mid) dfs(dfs, t[i].ls, l, mid);
			else dfs(dfs, t[i].rs, mid + 1, r);
		};
		dfs(dfs, rt, 0, n - 1);
		return rt;
	}

	Info rangeAsk(int rt, int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (i == 0 || qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + t[i].info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, t[i].ls, l, mid);
			dfs(dfs, t[i].rs, mid + 1, r);
		};
		dfs(dfs, rt, 0, n - 1);
		return res;
	} /// end-hash

	// lower_bound on prefix sums of difference between two versions.
	int lower_bound(int rt_l, int rt_r, Info val) { /// start-hash
		Info sum{};
		auto dfs = [&](auto &dfs, int x ,int y, int l, int r) {
			if (l == r) return sum + t[y].info - t[x].info >= val ? l : l + 1;
			int mid = (l + r) >> 1;
			Info s = t[t[y].ls].info - t[t[x].ls].info;
			if (sum + s >= val) return dfs(dfs, t[x].ls, t[y].ls, l, mid);
			else {
				sum = sum + s;
				return dfs(dfs, t[x].rx, t[y].rs, mid + 1, r);
			}
		};
		return dfs(dfs, rt_l, rt_r, 0, n - 1);
	} /// end-hash
};
