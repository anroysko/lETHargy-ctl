/**
 * Author: Yuhao Yao.
 * Date: 22-10-24
 * Description: Maximum weighted of Linear Base of vector space $\mathbb{Z}_2^{d}$.
 *  $T$ is the type of vectors and $Z$ is the type of weights.
 *  $w[i]$ is the non-negative weight of a[i]. Keep $w[]$ zero to use unweighted Linear Base.
 * Time: O(d \cdot \frac{d}{w}) for insertion; O(d^2 \cdot \frac{d}{w}) for union.
 * Status: tested on https://codeforces.com/contest/1100/problem/F, https://ac.nowcoder.com/acm/contest/11194/E, https://codeforces.com/gym/102156/problem/D.
 */
template<int d, class T = bitset<d>, class Z = int>
struct LB {
	/// start-hash
	#define revrep(i, a, n) for (auto i = n; i >= (a); --i)
	vector<T> a;
	vector<Z> w;

	T& operator [](int i) const { return (T&)a[i]; }
	LB(): a(d), w(d) {}
	
	// insert x. return 1 if the base is expanded.
	int insert(T x, Z val = 0) {
		revrep(i, 0, d - 1) if (x[i]) {
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
		revrep(i, 0, d - 1) {
			if (x[i] && w[i] >= val) x ^= a[i]; // change x[i] to x[i] == 0 to ask maximum value we can get.
		}
		return x;
	} /// end-hash

	// take the union of two bases.
	friend LB operator +(LB a, const LB &b) { /// start-hash
		rep(i, 0, d - 1) if (b[i] != 0) a.insert(b[i]);
		return a;
	} /// end-hash

	// return the k-th smallest value spanned by vectors with wieght at least $val$. k starts from 0.
	// Time: O(d \cdot \frac{d}{w}).
	T kth(unsigned long long k, Z val = 0) { /// start-hash
		int N = 0;
		rep(i, 0, d - 1) N += (a[i] != 0 && w[i] >= val);
		if (k >= (1ull << N)) return -1; // return -1 if k is too large.
		T res = 0;
		revrep(i, 0, d - 1) if (a[i] != 0 && w[i] >= val) {
			--N;
			auto bit = k >> N & 1;
			if (res[i] != bit) res ^= a[i];
		}
		return res;
	} /// end-hash
};