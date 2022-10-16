/**
 * Author: Yuhao Yao
 * Description: Fast Fourier Transform.
 * Time: O(N \log N)
 */
#pragma once

// use T = double or long double.
template<class T> struct FFT {
	using cp = complex<T>;
	static constexpr T pi = acos(T{-1});
	vi r;
	int n2;

	void dft(vector<cp> &a, int is_inv) { // is_inv == 1 -> idft.
		rep(i, 1, n2 - 1) if (r[i] > i) swap(a[i], a[r[i]]);
		for(int step = 1; step < n2; step <<= 1) {
			vector<cp> w(step);
			rep(j, 0, step-1) { // this has higher precision, compared to using the power of zeta.
				T theta = pi * j / step;
				if (is_inv) theta = -theta;
				w[j] = cp{cos(theta), sin(theta)};
			}
			for (int i = 0; i < n2; i += step << 1) {
				rep(j, 0, step - 1) {
					cp tmp = w[j] * a[i + j + step];
					a[i + j + step] = a[i + j] - tmp;
					a[i + j] += tmp;
				}
			}
		}
		if (is_inv) {
			for (auto &x: a) x /= n2;
		}
	}
	void pre(int n) { // set n2, r;
		int len = 0;
		for (n2 = 1; n2 < n; n2 <<= 1) len++;
		r.resize(n2);
		rep(i, 1, n2 - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}
	template<class Z> vector<Z> conv(const vector<Z> &A, const vector<Z> &B) {
		int n = sz(A) + sz(B) - 1;
		pre(n);
		vector<cp> a(n2, 0), b(n2, 0);
		rep(i, 0, sz(A) - 1) a[i] = A[i];
		rep(i, 0, sz(B) - 1) b[i] = B[i];
		
		dft(a, 0); dft(b, 0);
		rep(i, 0, n2 - 1) a[i] *= b[i];
		dft(a, 1);
		vector<Z> res(n);
		T eps = T{0.5} * (static_cast<Z>(1e-9) == 0);
		rep(i, 0, n - 1) res[i] = a[i].real() + eps;
		return res;
	}
	vi conv(const vi &A, const vi &B, int mod) {
		int M = sqrt(mod) + 0.5;
		int n = sz(A) + sz(B) - 1;
		pre(n);
		vector<cp> a(n2, 0), b(n2, 0), c(n2, 0), d(n2, 0);
		rep(i, 0, sz(A) - 1) a[i] = A[i] / M, b[i] = A[i] % M;
		rep(i, 0, sz(B) - 1) c[i] = B[i] / M, d[i] = B[i] % M;
		
		dft(a, 0); dft(b, 0); dft(c, 0); dft(d, 0);
		vi res(n);

		auto work = [&](vector<cp> &a, vector<cp> &b, int w, int mod) {
			vector<cp> tmp(n2);
			rep(i, 0, n2 - 1) tmp[i] = a[i] * b[i];
			dft(tmp, 1);
			rep(i, 0, n - 1) res[i] = (res[i] + (ll)(tmp[i].real() + 0.5) % mod * w) % mod;
		};
		work(a, c, 1ll * M * M % mod, mod);
		work(b, d, 1, mod);
		work(a, d, M, mod);
		work(b, c, M, mod);
		return res;
	}
};