/**
 * Author: Yuhao Yao
 * Description: Disjoint set union.
 * Time: amortized O(\alpha(M, N)) where $M$ is the number of operations. Almost constant in competitive programming.
 */

struct DSU {
	vi fa, siz;

	DSU(int n): fa(n), siz(n, 1) { iota(all(fa), 0); }
	
	int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

	bool check(int x, int y) { return getfa(x) != getfa(y); }

	// return 1 if x and y are in different component and merge.
	bool merge(int x, int y) {
		int fx = getfa(x), fy = getfa(y);
		if (fx == fy) return 0;
		if (siz[fx] < siz[fy]) swap(fx, fy);
		fa[fy] = fx;
		siz[fx] += siz[fy];
		return 1;
	}
};