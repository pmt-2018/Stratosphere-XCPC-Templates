const ll mod[3] = {900000011, 998244353, 1000000007};
const ll bas[3] = {4493, 8111, 8527};
ll pw[3][S], Hash[3][S];
inline ll getHash(int id, int L, int R) {  // str[L..R-1]
	ll J = (Hash[id][R] - Hash[id][L] * pw[id][R - L]) % mod[id];
	return J < 0 ? J + mod[id] : J;
}
void init(char* s, int n) {
	for (int j = 0; j < 3; j++) {
		f = Hash[j], f[0] = 0;
		g = pw[j], g[0] = 1;
		for (int i = 1; i <= n; i++) {
			f[i] = (f[i - 1] * bas[j] + (s[i] - 'a')) % mod[j];
			g[i] = g[i - 1] * bas[j] % mod[j];
		}
	}
}
