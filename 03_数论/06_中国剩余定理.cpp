// ---
// 解方程：
// \[
//     \begin{cases}
//         x\equiv a_1(\bmod\ m_1)\\
//         x\equiv a_2(\bmod\ m_2)\\
//         \vdots\\
//         x\equiv a_n(\bmod\ m_n)
//     \end{cases}
// \]
// 若 $m_i$ 两两互质，则可以使用以下公式得到：
// \[
// \begin{aligned}
//     x \equiv \sum_{i=1}^n M_i \times N_i \times a_i (\bmod\ M)\\
//     \text{where:}
//     \begin{cases}
//         M = \prod_{i=1}^n m_i \\
//         M_i = \frac{M}{m_i}\\
//         N_i \times M_i \equiv 1 (\bmod\ m_i)
//     \end{cases}
// \end{aligned}
// \]
// 否则参考以下exCRT。
// ---
ll exCRT(vector<int> a, vector<int> m) {
	assert(a.size() == m.size());
	ll ans = a[0], M = b[0];
	for (int i = 1; i < a.size(); i++) {
		ll x = 0, y = 0;
		ll A = M, B = m[i], C = (a[i] - ans % B + B) % B;
		ll gcd = exgcd(A, B, x, y), bg = B / gcd;
		x = x * (C / gcd) % B;
		ans += x * M;
		M *= bg;
		ans = (ans % M + M) % M;
	}
	return (ans % M + M) % M;
}
