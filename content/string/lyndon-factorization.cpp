/**
 * Author: Yuhao Yao
 * Date: 22-10-21
 * Description: Lyndon factorization of string $s$.
 * Time: O(|s|).
 * Status: tested on https://www.luogu.com.cn/problem/P6114.
**/
vector<string> duval(string const& s) {
	int n = sz(s), i = 0;
	vector<string> res;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while (i <= k) {
			res.push_back(s.substr(i, j - k));
			i += j - k;
		}
	}
	return res;
}