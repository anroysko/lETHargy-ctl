/**
 * Author: Yuhao Yao
 * Date: 22-08-13
 * Description: Modular integer. Note that there are several advantages to use this code:
	1. You do not need to keep writing \% $mod$;
	2. It is good to use this struct when doing Gaussian Elimination / Fast Walsh-Hadamard Transform;
	3. Sometimes the input number is greater than $mod$ and this code handles it.
 * Usage: $mod$ should be a global variable (either const int or int).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33191/F.
 */
#pragma once

template<const int &mod_> struct Z {
	/// start-hash
	static constexpr const int &mod = mod_;
	int x;
	Z(ll a = 0): x(a % mod) { if (x < 0) x += mod; }
	explicit operator int() const { return x; }

	Z& operator +=(Z b) { x += b.x; if (x >= mod) x -= mod; return *this; }
	Z& operator -=(Z b) { x -= b.x; if (x < 0) x += mod; return *this; }
	Z& operator *=(Z b) { x = 1ll * x * b.x % mod; return *this; }
	friend Z operator +(Z a, Z b) { return a += b; }
	friend Z operator -(Z a, Z b) { return a -= b; }
	friend Z operator *(Z a, Z b) { return a *= b; }
	/// end-hash

	// the following are needed for fft and polynomial operations.
	/// start-hash
	Z pow(ll k) const {
		Z res = 1, a = *this;
		for (; k; k >>= 1, a = a * a) if (k & 1) res = res * a;
		return res;
	}
	Z& operator /=(Z b) {
		assert(b.x != 0);
		*this = *this * b.pow(mod - 2);
		return *this;
	}
	friend Z operator /(Z a, Z b) { return a /= b; }
	/// end-hash

	friend string to_string(Z a) { return to_string(a.x); } // just for debug.
};
