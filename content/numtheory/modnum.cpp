/**
 * Author: Yuhao Yao
 * Ddescription: Modular integer. Note that there are several advantages to use this code:
	1. You do not need to keep writing \% $mod$;
	2. It is good to use this struct when doing Gaussian Elimination / Fast Walsh-Hadamard Transform;
	3. Sometimes the input number is greater than $mod$ and using this code just handles it.
 * Usage: mod should be a global variable (either const int or int).
 */
#pragma once

template<const int &mod_> struct Z {
	/// start-hash
	static constexpr int mod = mod_;
	int x;
	Z(ll a = 0): x(a % mod) { if (x < 0) x += mod; }

	static int norm(int x) { return x < 0 ? x + mod : x >= mod ? x - mod : x; }
	friend Z operator +(Z a, Z b) { a.x = norm(a.x + b.x); return a; }
	friend Z operator -(Z a, Z b) { a.x = norm(a.x - b.x); return a; }
	friend Z operator *(Z a, Z b) { a.x = 1ll * a.x * b.x % mod; return a; }
	/// end-hash

	Z& operator +=(Z b) { x = norm(x + b.x); return *this; }
	Z& operator -=(Z b) { x = norm(x - b.x); return *this; }

	static Z power(Z a, ll k) { /// start-hash
		Z res = 1;
		for (; k; k >>= 1, a = a * a) if (k & 1) res = res * a;
		return res;
	}
	friend Z operator /(Z a, Z b) { return a * power(b, mod - 2); }
	/// end-hash
};