/**
 * Author: Yuhao Yao
 * Date: 22-08-19
 * Description: Compute the intersection of a non-self-intersecting Polygon $poly$ and a Half Plane $ab$ (i.e. the LHS of $ab$).
 *  The returned Polygon can be self intersecting, so it can only be used for area relating problem.
 *  Only works for double or long double.
 * Time: O(|poly|).
 * Status: (double) tested on https://codeforces.com/gym/101611/problem/J.
 */
template<class P>
vector<P> cutPoly(const vector<P> &poly, P a, P b) {
	vector<P> res;
	rep(i, 0, sz(poly) - 1) {
		P p = poly[i];
		P q = poly[(i + 1) % sz(poly)];
		int sgn1 = P::sgn(p.dis_to_line(a, b));
		int sgn2 = P::sgn(q.dis_to_line(a, b));

		if (sgn1 <= 0) res.push_back(p);
		if (sgn1 * sgn2 == -1) {
			auto s0 = (p - a).cross(b - a);
			auto s1 = (p - q).cross(b - a);
			res.push_back(p + (q - p) * s0 / s1);
		}
	}
	return res;
}
