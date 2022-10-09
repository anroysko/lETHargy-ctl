/**
 * Author: Yuhao Yao
 * Date: 22-10-03
 * Description: Suffix Automaton. (Using map to store sons makes it 2~3 times slower but it should be fine in most cases.)
 *  $len$ is the length of the longest substring corresponding to the state. 
 *  $fa$ is the father in the prefix tree. Note that fa[i] < i doesn't hold.
 *  root is 0.
 * Usage: Use SAM sam(s) for string $s$ or vector $s$.
 * Time: O(|s|).
 * Status: tested on https://ac.nowcoder.com/acm/contest/884/I, https://ac.nowcoder.com/acm/contest/33188/H, https://codeforces.com/gym/101194/problem/F, https://nanti.jisuanke.com/t/A2018, https://darkbzoj.cc/problem/3238, https://nanti.jisuanke.com/t/A1623, https://www.spoj.com/problems/NSUBSTR/en/, https://codeforces.com/contest/235/problem/C.
 */

struct SAM {
	struct node { /// start-hash
		map<int, int> nxt;
		int fa, len;
		int occ, pos; // end of prefix
		node(int fa, int len): fa(fa), len(len) {
			occ = pos = 0;
		}
	};

	int n;
	vector<node> t;
	vi at; // at[i] = the state at which the i-th prefix is.
	SAM(const string &str): n(sz(str)), at(n) {
		t.emplace_back(-1, 0);
		int last = 0; // create root.

		rep(i, 0, n - 1) {
			int c = str[i];
			int now = last;
			t.emplace_back(-1, t[now].len + 1);
			last = sz(t) - 1;
			t[last].occ = 1;
			t[last].pos = i;
			at[i] = last;

			while (now != -1 && t[now].nxt.count(c) == 0) {
				t[now].nxt[c] = last;
				now = t[now].fa;
			}
			if (now == -1) t[last].fa = 0; // root is 0.
			else {
				int p = t[now].nxt[c];
				if (t[p].len == t[now].len + 1) t[last].fa = p;
				else {
					auto tmp = t[p];
					tmp.len = t[now].len + 1;
					tmp.occ = 0; // do not copy occ.
					t.push_back(tmp);
					int np = sz(t) - 1;

					t[last].fa = t[p].fa = np;
					while (now != -1 && t[now].nxt.count(c) && t[now].nxt[c] == p) {
						t[now].nxt[c] = np;
						now = t[now].fa;
					}
				}
			}
		}
	} /// end-hash

	void calOccurrence() { /// start-hash
		vi sum(n + 1), que(sz(t));
		for (auto &it: t) sum[it.len]++;
		rep(i, 1, n) sum[i] += sum[i - 1];
		rep(i, 0, sz(t) - 1) que[--sum[t[i].len]] = i;
		reverse(all(que));
		for (auto now: que) if (now != 0) t[t[now].fa].occ += t[now].occ;
	} /// end-hash
};