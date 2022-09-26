/**
 * Author: Yuhao Yao
 * Date: 22-09-26
 * Description: Call fail table of pattern string $p = p_0...p_{n - 1}$ in linear time and get all matched positions in text string $t$ in linear time.
 *  $fail[i]$ denotes the length of the border of substring $p_0...p_i$.
 * Usage: KMP kmp(s) for string $s$ or vector<int> $s$.
 * Time: O(|p|) for precalculation and O(|p| + |t|) for matching.
 * Status: tested on https://www.luogu.com.cn/problem/P6216, https://www.luogu.com.cn/problem/P5446.
 */
template<class T> struct KMP {
	int n;
	const T p;
	vi fail;

	KMP(const T &p): n(sz(p)), p(p), fail(n) {
		int j = 0;
		rep(i, 1, n - 1) {
			while (j > 0 && p[j] != p[i]) j = fail[j - 1];
			if (p[j] == p[i]) j++;
			fail[i] = j;
		}
	}

	// gets all matched (starting) positions.
	vi match(const T &t) {
		int m = sz(t), j = 0;
		vi res(m);
		rep(i, 0, m - 1) {
			while (j > 0 && (j == n || p[j] != t[i])) j = fail[j - 1];
			if (p[j] == t[i]) j++;
			if (j == n) res[i - n + 1] = 1;
		}
		return res;
	}
};