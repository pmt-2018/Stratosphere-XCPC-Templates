// ---
// by yhx-12243，暂未验证
// ---
const double eps = 1e-8;

#define lt(x, y) ((x) < (y)-eps)
#define gt(x, y) ((x) > (y) + eps)
#define le(x, y) ((x) <= (y) + eps)
#define ge(x, y) ((x) >= (y)-eps)
#define eq(x, y) (le(x, y) && ge(x, y))
#define dot(x, y, z) (((y) - (x)) * ((z) - (x)))
#define cross(x, y, z) (((y) - (x)) ^ ((z) - (x)))
struct vec2 {
	double x, y;
	vec2(double x0 = 0.0, double y0 = 0.0) : x(x0), y(y0) {}
	vec2* read() {
		scanf("%lf%lf", &x, &y);
		return this;
	}
	inline vec2 operator-() const { return vec2(-x, -y); }
	inline vec2 operator+(const vec2& B) const {
		return vec2(x + B.x, y + B.y);
	}
	inline vec2 operator-(const vec2& B) const {
		return vec2(x - B.x, y - B.y);
	}
	inline vec2 operator*(double k) const { return vec2(x * k, y * k); }
	inline vec2 operator/(double k) const { return *this * (1.0 / k); }
	inline double operator*(const vec2& B) const { return x * B.x + y * B.y; }
	inline double operator^(const vec2& B) const { return x * B.y - y * B.x; }
	inline double norm2() const { return x * x + y * y; }
	inline double norm() const { return sqrt(x * x + y * y); }
	inline bool operator<(const vec2& B) const {
		return lt(x, B.x) || le(x, B.x) && lt(y, B.y);
	}
	inline bool operator==(const vec2& B) const {
		return eq(x, B.x) && eq(y, B.y);
	}
	inline bool operator<<(const vec2& B) const {
		return lt(y, 0) ^ lt(B.y, 0)
		           ? lt(B.y, 0)
		           : gt(*this ^ B, 0)
		                 || ge(*this ^ B, 0) && ge(x, 0) && lt(B.x, 0);
	}
	inline vec2 trans(double a11, double a12, double a21, double a22) const {
		return vec2(x * a11 + y * a12, x * a21 + y * a22);
	}
};
/*
operator * : Dot product
operator ^ : Cross product
norm2() : |v|^2 = v.v
norm() : |v| = sqrt(v.v)
operator < : Two-key compare
operator << : Polar angle compare
trans : Transition with a 2x2 matrix
*/
struct line {
	double A, B, C;  // Ax + By + C = 0, > 0 if it represents halfplane.
	line(double A0 = 0.0, double B0 = 0.0, double C0 = 0.0)
	    : A(A0), B(B0), C(C0) {}
	line(const vec2& u, const vec2& v)
	    : A(u.y - v.y), B(v.x - u.x), C(u ^ v) {}  // left > 0
	inline vec2 normVec() const { return vec2(A, B); }
	inline double norm2() const { return A * A + B * B; }
	inline double operator()(const vec2& P) const {
		return A * P.x + B * P.y + C;
	}
};
inline vec2 intersection(const line u, const line v) {
	return vec2(u.B * v.C - u.C * v.B, u.C * v.A - u.A * v.C)
	       / (u.A * v.B - u.B * v.A);
}
inline bool parallel(const line u, const line v) {
	double p = u.normVec() ^ v.normVec();
	return eq(p, 0);
}
inline bool perpendicular(const line u, const line v) {
	double p = u.normVec() * v.normVec();
	return eq(p, 0);
}
inline bool sameDir(const line u, const line v) {
	return parallel(u, v) && gt(u.normVec() * v.normVec(), 0);
}
inline line bisector(const vec2 u, const vec2 v) {
	return line(v.x - u.x, v.y - u.y, 0.5 * (u.norm2() - v.norm2()));
}
inline double dis2(const vec2 P, const line l) {
	return l(P) * l(P) / l.norm2();
}
inline vec2 projection(const vec2 P, const line l) {
	return P - l.normVec() * (l(P) / l.norm2());
}
inline vec2 symmetry(const vec2 P, const line l) {
	return P - l.normVec() * (2 * l(P) / l.norm2());
}
// Relation of 3 points. (2 inside, 1 outside, 0 not collinear)
inline int collinear(const vec2 u, const vec2 v, const vec2 P) {
	double p = cross(P, u, v);
	return eq(p, 0) ? 1 + le(dot(P, u, v), 0) : 0;
}
// Perimeter of a polygon
double perimeter(int n, vec2* poly) {
	double ret = (poly[n - 1] - *poly).norm();
	for (int i = 1; i < n; ++i) ret += (poly[i - 1] - poly[i]).norm();
	return ret;
}
// Directed area of a polygon (positive if CCW)
double area(int n, vec2* poly) {
	double ret = poly[n - 1] ^ *poly;
	for (int i = 1; i < n; ++i) ret += poly[i - 1] ^ poly[i];
	return ret * 0.5;
}
// Point in polygon (2 on boundary, 1 inside, 0 outside)
int contain(int n, vec2* poly, const vec2 P) {
	int in = 0;
	vec2 *r = poly + (n - 1), *u, *v;
	for (int i = 0; i < n; r = poly, ++poly, ++i) {
		if (collinear(*r, *poly, P) == 2) return 2;
		gt(r->y, poly->y) ? (u = poly, v = r) : (u = r, v = poly);
		if (ge(P.y, v->y) || lt(P.y, u->y)) continue;
		in ^= gt(cross(P, *u, *v), 0);
	}
	return in;
}
// Convex Hall
int graham(int n, vec2* p, vec2* dest) {
	int i;
	vec2* ret = dest;
	std::iter_swap(p, std::min_element(p, p + n));
	std::sort(p + 1, p + n, [p](const vec2 A, const vec2 B) {
		double r = cross(*p, A, B);
		return gt(r, 0) || (ge(r, 0) && lt((A - *p).norm2(), (B - *p).norm2()));
	});
	for (i = 0; i < 2 && i < n; ++i) *ret++ = p[i];
	for (; i < n; *ret++ = p[i++])
		for (; ret != dest + 1 && ge(cross(ret[-2], p[i], ret[-1]), 0); --ret)
			;
	return *ret = *p, ret - dest;
}
double convDiameter(int n, vec2* poly) {
	int l = std::min_element(poly, poly + n) - poly,
	    r = std::max_element(poly, poly + n) - poly, i = l, j = r;
	double diam = (poly[l] - poly[r]).norm2();
	do {
		(ge(poly[(i + 1) % n] - poly[i] ^ poly[(j + 1) % n] - poly[j], 0)
		     ? ++j
		     : ++i) %= n;
		up(diam, (poly[i] - poly[j]).norm2());
	} while (i != l || j != r);
	return diam;
}
//
inline vec2 circumCenter(const vec2 A, const vec2 B, const vec2 C) {
	vec2 a = B - A, b = C - A, AO;
	double det = 0.5 / (a ^ b), na = a.norm2(), nb = b.norm2();
	AO = vec2((na * b.y - nb * a.y) * det, (nb * a.x - na * b.x) * det);
	return A + AO;
}
double minCircleCover(int n, vec2* p, vec2* ret = NULL) {
	int i, j, k;
	double r2 = 0.0;
	std::random_shuffle(p + 1, p + (n + 1));
	vec2 C = p[1];
	for (i = 2; i <= n; ++i)
		if (gt((p[i] - C).norm2(), r2))
			for (C = p[i], r2 = 0, j = 1; j < i; ++j)
				if (gt((p[j] - C).norm2(), r2))
					for (C = (p[i] + p[j]) * 0.5, r2 = (p[j] - C).norm2(),
					    k = 1;
					     k < j; ++k)
						if (gt((p[k] - C).norm2(), r2))
							C = circumCenter(p[i], p[j], p[k]),
							r2 = (p[k] - C).norm2();
	return ret ? *ret = C : 0, r2;
}
//半平面交
inline bool HPIcmp(const line u, const line v) {
	return sameDir(u, v) ? gt((fabs(u.A) + fabs(u.B)) * v.C,
	                          (fabs(v.A) + fabs(v.B)) * u.C)
	                     : u.normVec() << v.normVec();
}
inline bool geStraight(const vec2 A, const vec2 B) {
	return lt(A ^ B, 0) || le(A ^ B, 0) && lt(A * B, 0);
}
inline bool para_nega_test(const line u, const line v) {
	return parallel(u, v) && lt(u.normVec() * v.normVec(), 0)
	       && (fabs(u.A) + fabs(u.B)) * v.C + (fabs(v.A) + fabs(v.B)) * u.C
	              < -7e-14;
}
int HPI(int n, line* l, vec2* poly, vec2*& ret) {  // -1 : Unbounded, -2 :
	Infeasible int h = 0, t = -1, i, j, que[n + 5];
	std::sort(l, l + n, HPIcmp);
	n = std::unique(l, l + n, sameDir) - l;
	for (j = i = 0; i < n && j < n; ++i) {
		for (up(j, i + 1); j < n && !geStraight(l[i].normVec(), l[j].normVec());
		     ++j)
			;
		if (para_nega_test(l[i], l[j])) return -2;
	}
	if (n <= 2 || geStraight(l[n - 1].normVec(), l->normVec())) return -1;
	for (i = 0; i < n; ++i) {
		if (geStraight(l[que[t]].normVec(), l[i].normVec())) return -1;
		for (; h < t && le(l[i](poly[t - 1]), 0); --t)
			;
		for (; h < t && le(l[i](poly[h]), 0); ++h)
			;
		que[++t] = i;
		h < t ? poly[t - 1] = intersection(l[que[t - 1]], l[que[t]]) : 0;
	}
	for (; h < t && le(l[que[h]](poly[t - 1]), 0); --t)
		;
	return h == t ? -2
	              : (poly[t] = intersection(l[que[t]], l[que[h]]),
	                 ret = poly + h, t - h + 1);
}
// circles
const double pi = M_PI, pi2 = pi * 2., pi_2 = M_PI_2;
inline double angle(const vec2 u, const vec2 v) { return atan2(u ^ v, u * v); }
// intersection of circle and line
int intersection(double r2, const vec2 O, const line l, vec2* ret) {
	double d2 = dis2(O, l);
	vec2 j = l.normVec();
	if (gt(d2, r2)) return ret[0] = ret[1] = vec2(INFINITY, INFINITY), 0;
	if (ge(d2, r2)) return ret[0] = ret[1] = projection(O, l), 1;
	if (le(d2, 0)) {
		j = j * sqrt(r2 / j.norm2());
		ret[0] = O + j.trans(0, -1, 1, 0);
		ret[1] = O + j.trans(0, 1, -1, 0);
	} else {
		double T = copysign(sqrt((r2 - d2) / d2), l(O));
		j = j * (-l(O) / j.norm2());
		ret[0] = O + j.trans(1, T, -T, 1);
		ret[1] = O + j.trans(1, -T, T, 1);
	}
	return 2;
}
// area of intersection(x^2 + y^2 = r^2, triangle OBC)
double interArea(double r2, const vec2 B, const vec2 C) {
	if (eq(B ^ C, 0)) return 0;
	vec2 is[2];
	if (!intersection(r2, vec2(), line(B, C), is))
		return 0.5 * r2 * angle(B, C);
	bool b = gt(B.norm2(), r2), c = gt(C.norm2(), r2);
	if (b && c)
		return 0.5
		       * (lt(dot(*is, B, C), 0)
		              ? r2 * (angle(B, *is) + angle(is[1], C)) + (is[0] ^ is[1])
		              : r2 * angle(B, C));
	else if (b) return 0.5 * (r2 * angle(B, *is) + (*is ^ C));
	else if (c) return 0.5 * ((B ^ is[1]) + r2 * angle(is[1], C));
	else return 0.5 * (B ^ C);
}
// tangents to circle((0, 0), r) through P
int tangent(double r, const vec2 P, line* ret) {
	double Q = P.norm2() - r * r;
	if (lt(Q, 0))
		return ret[0] = ret[1] = line(INFINITY, INFINITY, INFINITY), 0;
	if (le(Q, 0)) return ret[0] = ret[1] = line(P.x, P.y, -P.norm2()), 1;
	Q = sqrt(Q) / r;
	ret[0] = line(P.x + Q * P.y, P.y - Q * P.x, -P.norm2());
	ret[1] = line(P.x - Q * P.y, P.y + Q * P.x, -P.norm2());
	return 2;
}
// tangets to circle(O, r) through P
int tangent(double r, const vec2 O, const vec2 P, line* ret) {
	int R = tangent(r, P - O, ret);
	if (R)
		ret[0].C -= ret[0].A * O.x + ret[0].B * O.y,
		    ret[1].C -= ret[1].A * O.x + ret[1].B * O.y;
	return R;
}