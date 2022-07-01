/**
 * Author: Yuhao Yao
 * Description: Fast Walsh-Hadamard Transform fwt(a) = (\sum_i (-1)^{pc(i\&0)} a_i, ..., \sum_i (-1)^{pc(i\&n-1)} a_i). One can use it to do xor-convolution.
 * Usage: $N$ should be a power of $2$.
 * Time: O(N \log N).
 */

template<class T> void fwt(vector<T> &a, int is_inv) {
    int N = sz(a);
    for (int i = 1; i < N; i <<= 1)
        for (int p = i << 1, j = 0; j < N; j += p)
            rep(k, 0, i - 1) {
                T x = a[j + k], y = a[i + j + k];
                a[j + k] = x + y; 
                a[i + j + k] = x - y;
            }
 
    if (is_inv) {
        for(auto &x: a) x = x / N;
    }
}