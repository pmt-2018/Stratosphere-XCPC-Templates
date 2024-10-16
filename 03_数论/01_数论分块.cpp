// ---
// \noindent 每一次 $[l,r]$ 都是 $n/l = n/r , m/l = m/r$ 的极大区间。\\
// 多个 $n, m$ 只要对多个 $n/(n/l)$ 取 $\min$ 即可，复杂度为$O(|cnt|\sqrt V)$
// ---
for (ll l = 1, r = 1; l <= min(n, m); l = r + 1) {
	r = min(n / (n / l), m / (m / l));
	// Do something here
}