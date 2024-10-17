const int N = 1e6;
double inv[maxn];
void sieve() {
	// 见线性筛部分
	for (int i = 1; i <= N; ++i) inv[i] = 1.0 / i;
}
ll val[maxn], pos[maxn], id1[maxn], id2[maxn], cnt;
ll solve(ll n) {
	ll T = sqrt(n) + 3;
	for (ll i = 1, pi; i <= n; i = pi + 1) {
		pos[++cnt] = n / i;
		pi = n / pos[cnt];
		val[cnt] = pos[cnt] - 1;
		(n / i <= T ? id1[n / i] : id2[pi]) = cnt;
	}
	auto getid = [&](ll x) -> int { return x <= T ? id1[x] : id2[n / x]; };
	for (int i = 1; 1ll * prime[i] * prime[i] <= n; i++) {
		int p = id1[prime[i - 1]];
		for (int j = 1; pos[j] >= 1ll * prime[i] * prime[i]; j++) {
			int q = getid(1.0 * pos[j] * inv[prime[i]] + 1e-7);
			val[j] -= val[q] - val[p];
		}
	}
	return val[1];
}