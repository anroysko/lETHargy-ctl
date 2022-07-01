/**
 * Author: Yuhao Yao
 * Description: Number Theoretic Transform. Use modnum as template parameter.
 */
#pragma once

template<class T> struct FFT {
	const T g; // primitive root.
	vi r;
	int n2, len;

	FFT(): g(3) {}

	void dft(vector<T> &a, int is_inv) { // is_inv == 1 -> idft.
		rep(i, 1, n2 - 1) if (r[i] > i) swap(a[i], a[r[i]]);
		rep(t, 0, len - 1) {
			int step = 1 << t, step2 = step << 1;
			vector<T> w(step);
			T zeta = T::pow(g, (T::mod - 1) / step2);
			if (is_inv) zeta = 1 / zeta;

			w[0] = 1;
			rep(i, 1, step - 1) w[i] = w[i - 1] * zeta;
			for (int i = 0; i < n2; i += step2) {
				rep(j, 0, step - 1) {
					T tmp = w[j] * a[i + j + step];
					a[i + j + step] = a[i + j] - tmp;
					a[i + j] = a[i + j] + tmp;
				}
			}
		}

		if (is_inv == 1) {
			T inv = T{1} / n2;
			rep(i, 0, n2 - 1) a[i] *= inv;
		}
	}
	
	void pre(int n) { // set n2, r; also used in polynomial inverse.
		len = 0;
		for (n2 = 1; n2 < n; n2 <<= 1) len++;
		r.resize(n2);
		rep(i, 1, n2 - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (len - 1));
	}

	vector<T> conv(vector<T> a, vector<T> b) {
		int n = sz(a) + sz(b) - 1;
		pre(n);
		a.resize(n2, 0);
		b.resize(n2, 0);
		dft(a, 0); dft(b, 0);
		rep(i, 0, n2 - 1) a[i] *= b[i];
		dft(a, 1);
		a.resize(n);
		return a;
	}
};