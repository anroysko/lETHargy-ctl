/**
 * Author: Yuhao Yao
 * Description: Let $f(x)$ be a continuous function over $[a, b]$ having a fourth derivative,
 *  $f^{(4)}(x)$, over this interval. If $M$ is the maximum value of $|f^{(4)}(x)|$ over $[a, b]$,
 *  then the upper bound for the error is $O(\frac{M(b - a)^5}{N^4})$.
 * Time: O(N \cdot T), where $T$ is the time for evaluating $f$ once.
 */
template<class T = db> T SimpsonsRule(const function<T(T)> &f, T a, T b, int N = 1'000) {
	T res = 0;
	T h = (b - a) / (N * 2);
	res += f(b);
	res += f(a);
	rep(i, 1, N * 2 - 1) res += f(a + h * i) * (i & 1 ? 4 : 2);
	return res * h / 3;
}