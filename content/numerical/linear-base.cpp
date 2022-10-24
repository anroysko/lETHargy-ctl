/**
 * Author: Yuhao Yao.
 * Description: Maximum weighted of Linear Base of vector space $\mathbb{Z}_2^{LG}$.
 * Usage: keep w[] zero to use unweighted Linear Base.
 * Time: O(LG \cdot \frac{LG}{w}) for insertion; O(LG^2 \cdot \frac{LG}{w}) for union.
 * Status: tested at https://codeforces.com/contest/1100/problem/F and https://ac.nowcoder.com/acm/contest/11194/E.
 */

// T is the type of vectors and Z is the type of weights.
// w[i] is the non-negative weight of a[i].
template<int LG, class T = bitset<LG>, class Z = int> struct LB {
	/// start-hash
	#define revrep(i, a, n) for (auto i = n; i >= (a); --i)
	vector<T> a;
	vector<Z> w;

	T& operator [](int i) const { return (T&)a[i]; }
	LB(): a(LG), w(LG) {}
	
	// insert x. return 1 if the base is expanded.
	int insert(T x, Z val = 0) {
		revrep(i, 0, LG - 1) if (x[i]) {
			if (a[i] == 0) {
				a[i] = x;
				w[i] = val;
				return 1;
			} else if (val > w[i]) {
				swap(a[i], x);
				swap(w[i], val);
			}
			x ^= a[i];
		}
		return 0;
	} /// end-hash

	// min value we can get if we add vectors from linear base (with weight at least $val$) to $x$.
	T ask_min(T x, Z val = 0) { /// start-hash
		revrep(i, 0, LG - 1) {
			if (x[i] && w[i] >= val) x ^= a[i]; // change x[i] to x[i] == 0 to ask maximum value we can get.
		}
		return x;
	} /// end-hash

	// take the union of two bases.
	friend LB operator +(LB a, const LB &b) { /// start-hash
		rep(i, 0, LG - 1) if (b[i] != 0) a.insert(b[i]);
		return a;
	} /// end-hash

	// return the k-th smallest value spanned by vectors with wieght at least $val$. k starts from 0.
	// Time: O(LG \cdot \frac{LG}{w}).
	T kth(unsigned long long k, Z val = 0) { /// start-hash
		int N = 0;
		rep(i, 0, LG - 1) N += (a[i] != 0 && w[i] >= val);
		if (k >= (1ull << N)) return -1; // return -1 if k is too large.
		T res = 0;
		revrep(i, 0, LG - 1) if (a[i] != 0 && w[i] >= val) {
			--N;
			auto d = k >> N & 1;
			if (res[i] != d) res ^= a[i];
		}
		return res;
	} /// end-hash
};