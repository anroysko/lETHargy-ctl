/**
 * Author: Yuhao Yao
 * Description: Let $b = fwt(a)$. One can calculate $b_i$ for some index $i$ in $O(N)$ time.
 * Usage: $N$ should be a power of $2$.
 * Time: O(N).
 */

template<class T> T fwt_eval(const vector<T> &a, int id) {
    int N = sz(a);
    T res = 0;
    rep(k, 0, N - 1) {
        if (__builtin_popcount(k & id) & 1) res -= a[k];
        else res += a[k];
    }
    return res;
}