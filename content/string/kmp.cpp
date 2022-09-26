/**
 * Author: Yuhao Yao
 * Date: 22-09-26
 * Description: Compute fail table of pattern string $s = s_0...s_{n - 1}$ in linear time and get all matched positions in text string $t$ in linear time.
 *  $fail[i]$ denotes the length of the border of substring $p_0...p_i$.
 * Usage: KMP kmp(s) for string $s$ or vector<int> $s$.
 * Time: O(|p|) for precalculation and O(|p| + |t|) for matching.
 * Status: tested on https://www.luogu.com.cn/problem/P6216, https://www.luogu.com.cn/problem/P5446, https://www.codechef.com/submit/SSTRPREF2.
 */
template<class T> struct KMP {
	const T s;
	int n;
	vi fail;

	KMP(const T &s): s(s), n(sz(s)), fail(n) {
		int j = 0;
		rep(i, 1, n - 1) {
			while (j > 0 && s[j] != s[i]) j = fail[j - 1];
			if (s[j] == s[i]) j++;
			fail[i] = j;
		}
	}

	// gets all matched (starting) positions.
	vi match(const T &t) {
		int m = sz(t), j = 0;
		vi res(m);
		rep(i, 0, m - 1) {
			while (j > 0 && (j == n || s[j] != t[i])) j = fail[j - 1];
			if (s[j] == t[i]) j++;
			if (j == n) res[i - n + 1] = 1;
		}
		return res;
	}
};