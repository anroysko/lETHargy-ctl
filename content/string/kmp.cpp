/**
 * Author: Yuhao Yao
 * Description: Call fail table of pattern string $p$ in linear time and get all matched positions in text string $t$ in linear time.
 * Usage: KMP kmp(s) for string $s$ or vector<int> $s$.
 * Time: O(|p|) for precalculation and O(|p| + |t|) for matching.
 * Status: Not fully tested.
 */
template<class T> struct KMP {
	int n;
	T p;
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
	vector<bool> match(const T &t) {
		int m = sz(t), j = 0;
		vector<bool> res(m);
		rep(i, 0, m - 1) {
			while (j && (j == n || p[j] != t[i])) j = fail[j - 1];
			if (p[j] == t[i]) j++;
			if (j == n) res[i - n + 1] = 1;
		}
		return res;
	}
};