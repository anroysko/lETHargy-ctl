/**
 * Author: Yuhao Yao
 * Date: 22-07-23
 * Description: Matrix struct. Used for Gaussian elimination or inverse of matrix.
 * Usage: To solve $A x =  b^\top$, call SolveLinear(A, b).
 *  Besides, you need function $isZero$ for your template $T$.
 * Time: O(n m \min\{n, m\}) for Gaussian, inverse and SolveLinear.
 * Status: inverse is tested on https://ac.nowcoder.com/acm/contest/33187/J; SolveLinear is not tested yet.
 */

template<class T> struct Matrix {
	using Mat = Matrix;
	using Vec = vector<T>;

	vector<Vec> a;

	Matrix(int n, int m) { 
		assert(n > 0 && m > 0);
		a.assign(n, Vec(m));
	}
	Matrix(const vector<Vec> &a): a(a) {
		assert(sz(a) > 0 && sz(a[0]) > 0);
	}

	Vec& operator [](int i) const { return (Vec&) a[i]; }

	Mat operator + (const Mat &b) const {
		int n = sz(a), m = sz(a[0]);
		Mat c(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1) c[i][j] = a[i][j] + b[i][j];
		return c;
	}

	Mat operator - (const Mat &b) const {
		int n = sz(a), m = sz(a[0]);
		Mat c(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1) c[i][j] = a[i][j] - b[i][j];
		return c;
	}

	Mat operator *(const Mat &b) const {
		int n = sz(a), m = sz(a[0]), l = sz(b[0]);
		assert(m == sz(b.a));
		Mat c(n, l);
		rep(i, 0, n - 1) rep(k, 0, m - 1) rep(j, 0, l - 1) c[i][j] += a[i][k] * b[k][j];
		return c;
	}

	Mat tran() const {
		int n = sz(a), m = sz(a[0]);
		Mat res(m, n);
		rep(i, 0, n - 1) rep(j, 0, m - 1) res[j][i] = a[i][j];
		return res;
	}

	// do elimination for the first C columns, return the rank.
	int Gaussian(int C) {
		int n = sz(a), m = sz(a[0]), rk = 0;
		assert(C <= m);
		rep(c, 0, C - 1) {
			int id = rk;
			while (id < n && ::isZero(a[id][c])) id++;
			if (id == n) continue;
			if (id != rk) swap(a[id], a[rk]);

			T tmp = a[rk][c];
			for (auto &x: a[rk]) x /= tmp;
			rep(i, 0, n - 1) if (i != rk) {
				T fac = a[i][c];
				rep(j, 0, m - 1) a[i][j] -= fac * a[rk][j];
			}
			rk++;
		}
		return rk;
	}

	Mat inverse() const {
		int n = sz(a), m = sz(a[0]);
		assert(n == m);
		auto b = *this;

		rep(i, 0, n - 1) b[i].resize(n * 2, 0), b[i][n + i] = 1;
		assert(b.Gaussian(n) == n);
		for (auto &row: b.a) row.erase(row.begin(), row.begin() + n);
		return b;
	}

	friend pair<bool, Vec> SolveLinear(Mat A, const Vec &b) {
		#define revrep(i, a, n) for (auto i = n; i >= (a); --i)

		int n = sz(b);
		assert(sz(A.a) == n);
		rep(i, 0, n - 1) A[i].push_back(b[i]);
		int rk = A.Gaussian(sz(A[0]) - 1);
		rep(i, rk, n - 1) if (!::isZero(A[i].back())) return {0, Vec{}};
		Vec res(n);
		reverep(i, 0, n - 1) {
			T x = b[i];
			int last = -1;
			revrep(j, 0, sz(A[0]) - 1) if (!::isZero(A[i][j])) {
				x -= A[i][j] * res[j];
				last = j;
			}
			if (last != -1) res[last] = x;
		}
		return {1, res};
	}
};