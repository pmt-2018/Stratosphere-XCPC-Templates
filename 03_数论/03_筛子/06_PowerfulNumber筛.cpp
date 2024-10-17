// ---
// 未验证，待补充。
// \par 求$\sum_{i=1}^n f(i)$，找到$g(i)$满足$\forall p\in
// \mathbf{P},f(p)=g(p)$，g可杜教筛。 \par 不妨假设 $g\ast h =
// f$，那么$h$仅在PN处有值，于是
// $$\begin{aligned} \sum_{i=1}^{n} f(i)&=\sum_{ij} g(i)h(j) \\ &= \sum_{i\le n}
// h(i) \sum_{j=1}^{n/i} g(j)\end{aligned}$$ \par 计算$h$依靠递推：
// $$\begin{aligned}
// f(p^k)&=\sum_{i+j=k}g(p^i)h(p^j)\\ h(p^k)&=f(p^k)-\sum_{i=0}^{k-1}h(p^i)g(p^{k-i})\end{aligned}$$
// ---

void power_num(int k, ll m, int h) {
	if (k > totp || m * prime[k] > n) {
		if (n / m <= N) add(ans, 1ll * h * sxphi[n / m] % MOD);
		else add(ans, 1ll * h * Sxphi[n / (n / m)] % MOD);
		return;
	}
	power_num(k + 1, m, h);
	ll p = 1ll * prime[k] * prime[k];
	for (int e = 2; m * p <= n; p *= prime[k], e++) {
		power_num(k + 1, m * p,
		          p % MOD * (prime[k] - 1) % MOD * (e - 1) % MOD * h % MOD);
	}
}