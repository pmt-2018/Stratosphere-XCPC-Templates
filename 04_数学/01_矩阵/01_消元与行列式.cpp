inline int Gauss(int n) {
	int rt = 1, w = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			while (a[j][i]) {
				int d = a[i][i] / a[j][i];
				for (int k = i; k <= n; k++)
					sub(a[i][k], 1ll * d * a[j][k] % MOD);
				swap(a[i], a[j]), w ^= 1;
			}
		}
	}
	for (int i = 1; i <= n; i++) rt = 1ll * rt * a[i][i] % MOD;
	if (w || !rt) return rt;
	return MOD - rt;
}