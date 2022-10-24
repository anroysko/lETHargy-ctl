/**
 * Author: Yuhao Yao.
 * Description: Intersection of two unweighted linear bases.
 * Usage: T should be of length at least $2 \cdot LG$.
 * Time: O(LG^2 \cdot \frac{LG}{w}).
 * Status: tested at https://ac.nowcoder.com/acm/contest/884/B.
 */

template<int LG, class T = bitset<LG * 2>> LB<LG, T> intersect(LB<LG, T> a, const LB<LG, T> &b) {
	LB<LG, T> res;
	rep(i, 0, LG - 1) if (a[i] != 0) a[i][LG + i] = 1;
	T msk(string(LG, '1'));
	rep(i, 0, LG - 1) {
		T x = a.ask_min(b[i]);
		if ((x & msk) != 0) a.insert(x);
		else {
			T y = 0;
			rep(j, 0, LG - 1) if (x[LG + j]) y ^= a[j];
			res.insert(y & msk);
		}
	}
	return res;
}