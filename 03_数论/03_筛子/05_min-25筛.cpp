// ---
// 未验证，待补充
// ---
void init_g() {
	for (ll l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);
		w[++tot] = n / l;
		g ^ k[tot] = sum(1..w [tot] ^ k);
		if (n / l <= N) ind1[n / l] = tot;
		else ind2[l] = tot;
	}
}
void calc_g() {
	for (int i = 1; i <= totp; i++) {
		for (int j = 1; j <= tot && prime[i] * prime[i] <= w[j]; j++) {
			ll k = w[j] / prime[i] <= N ? ind1[w[j] / prime[i]]
			                            : ind2[n / (w[j] / prime[i])];
			sub(g ^ e[j], prime[i] ^ e * (g ^ e[k] - sp ^ e[i - 1]));
		}
	}
}
ll S(ll x, int y) {
	cnt++;
	if (prime[y] >= x) return 0;
	ll k = x <= N ? ind1[x] : ind2[n / x];
	ll ans = f(g ^ e(x)) - f(sp ^ e[y]);
	for (int i = y + 1; i <= totp && prime[i] * prime[i] <= x; i++) {
		ll p = prime[i];
		for (int e = 1; p <= x; e++, p *= prime[i]) {
			add(ans, f(p) * (S(x / p, i) + (e != 1)));
		}
	}
	return ans % MOD;
}