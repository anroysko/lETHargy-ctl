/**
 * Author: Yuhao Yao
 * Date: 22-09-17
 * Description: Compute the tangent points from Point $a$ to Circle $(o, r)$. return empty vector if $a$ is not outside the given Circle.
 *  Only works for double or long double.
 * Status: 
 */
template<class T, class P = Point<T>>
vector<P> PointCircleTagentPoints(P a, P o, T r) {
	P u = o - a;
	if (P::cmp(u.len2(), r * r) <= 0) return {};
	T d = sqrt(max(u.len2() - r * r, T{0}));
	T theta = asin(min(r / u.len(), T{1}));
	P v = u.unit();
	return {a + v.rotate(-theta) * d, a + v.rotate(theta) * d};
}
