/**
 * Author: Yuhao Yao
 * Date: 22-08-15
 * Description: Compute the intersection points of a Circle and a Segment.
 *  Only works for double or long double.
 * Status: (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class T, class P = Point<T>>
vector<P> capCircleSeg(P o, T r, P a, P b) {
	T d = o.dis_to_line(a, b);
	if (abs(d) > r + P::eps) return {};
	P p = o.project_to_line(a, b), v = (b - a).unit();
	T len = sqrt(max(T{0}, r * r - d * d));
	vector<P> res;
	if ((p + v * len).on_seg(a, b)) res.push_back(p + v * len);
	if ((p - v * len).on_seg(a, b)) res.push_back(p - v * len);
	return res;
}
