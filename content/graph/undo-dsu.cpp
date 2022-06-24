/**
 * Author: Yuhao Yao
 * Description: Use old = get\_top() to get a save point; use undo(old) to go back to the save point.
 * Time: Amortized O(\log N)
 */
template<class T> class Undo_DSU {
private:
	vector<T> fa, siz;
	vector<pair<T*, T>> sta;

	void safechg(T &x, T y) { sta.pb({&x, x}); x = y; }

public:
	Undo_DSU(int n): fa(n), siz(n, 1) {
		iota(all(fa), 0);
	}

	int getfa(int x) {
		T res = 0;
		while (x != fa[x]) x = fa[x];
		return x;
	}

	bool merge(int x, int y) {
		int fx = getfa(x), fy = getfa(y);
		if (fx == fy) return 1;
		if (siz[fx] < siz[fy]) swap(fx, fy);
		safechg(fa[fy], fx);
		safechg(siz[fx], siz[fx] + siz[fy]);
		return 0;
	}

	int get_top() { return sz(sta); }

	void undo(int top) {
		while (sz(sta) > top) {
			*sta.back().first = sta.back().second;
			sta.pop_back();
		}
	}
};