/**
 * Author: Yuhao Yao
 * Date: 22-10-29
 * Description: Class to handle points in 2D-plane. Avoid using $T = int$. 
 * Status:
 *  project_to_line (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 *  dis_to_line (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 *  dis_to_seg (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class T> 
struct Point {
	using P = Point;
	using type = T;
	static constexpr T eps = 1e-9;
	static constexpr bool isInt = is_integral_v<T>;
	static int sgn(T x) { return (x > eps) - (x < -eps); }
	static int cmp(T x, T y) { return sgn(x - y); }

	T x, y;

	P operator +(P b) const { return P{x + b.x, y + b.y}; }
	P operator -(P b) const { return P{x - b.x, y - b.y}; }
	P operator *(T b) const { return P{x * b, y * b}; }
	P operator /(T b) const { return P{x / b, y / b}; }
	bool operator ==(P b) const { return cmp(x, b.x) == 0 && cmp(y, b.y) == 0; }
	bool operator <(P b) const { return cmp(x, b.x) == 0 ? cmp(y, b.y) < 0: x < b.x; }

	T len2() const { return x * x + y * y; }
	T len() const { return sqrt(x * x + y * y); }
	P unit() const {
		if (isInt) return *this; // for long long
		else return len() <= eps ? P{} : *this / len(); // for double / long double;
	}

	// dot and cross may lead to big relative error for imprecise point when the result is relatively smaller than the input magnitude.
	T dot(P b) const { return x * b.x + y * b.y; }
	T cross(P b) const { return x * b.y - y * b.x; }

	bool is_upper() const { return y > eps || (sgn(y) == 0 && x < -eps); }
	
	// return -1 if a has smaller pollar; return 1 if a has a larger pollar; return 0 o.w.
	static int argcmp(P a, P b) {
		if (a.is_upper() != b.is_upper()) return cmp(a.is_upper(), b.is_upper());
		return sgn(b.cross(a));
		// Taking unit makes it slower but I believe it is also safer. You can drop .unit() when you think the precision is not an issue.
		// atan2 is much slower.
	}

	P rot90() const { return P{-y, x}; }
	P rot270() const { return P{y, -x}; }
	
	// Possible precision error: 
	// Absolute error is multiplied by the magnitude while the resulting coordinates can have 0 as magnitude!
	P rotate(T theta) const {
		P a{cos(theta), sin(theta)};
		return P{x * a.x - y * a.y, x * a.y + y * a.x};
	}

	// Returns the signed projected length onto line $ab$. Return 0 if $a = b$.
	T project_len(P a, P b) const { /// start-hash
		if (isInt) return (*this - a).dot(b - a);
		else if (a == b) return 0;
		else return (*this - a).dot(b - a) / (b - a).len();
	} /// end-hash

	// Returns the signed distance to line $ab$. $a$ and $b$ should be distinct.
	T dis_to_line(P a, P b) const { /// start-hash
		assert((a - b).len2() > P::eps);
		if (isInt) return (*this - a).cross(b - a);
		else return (*this - a).cross(b - a) / (b - a).len();
	} /// end-hash
	
	// Returns the distance to line segment $ab$. Safe when $a = b$.
	// Only for double / long double.
	T dis_to_seg(P a, P b) const { /// start-hash
		if (project_len(a, b) <= eps) return (*this - a).len();
		if (project_len(b, a) <= eps) return (*this - b).len();
		return fabs(dis_to_line(a, b));
	} /// end-hash

	// Calculate the projection to line $ab$. Return $a$ when $a = b$.
	// Only for double / long double.
	P project_to_line(P a, P b) const { /// start-hash
		return a + (b - a).unit() * project_len(a, b);
	} /// end-hash

	// Check if it is on segment ab. Safe when a == b.
	bool on_seg(P a, P b) const {  /// start-hash
		return dis_to_seg(a, b) <= eps; 
	}  /// end-hash

	// Check if it is on line $ab$. Need $a != b$.
	bool on_line(P a, P b) const {  /// start-hash
		return sgn(dis_to_line(a, b)) == 0;
	}  /// end-hash
	
	friend string to_string(P p) { return "(" + to_string(p.x) + ", " + to_string(p.y) + ")"; }
};
