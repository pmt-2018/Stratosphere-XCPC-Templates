// ---
// $$C_i = \sum_{j\oplus k = i}A_j\times B_k$$。
// $A$, $B$ FWT后对应位相乘在iFWT回去。
// ---
// op = 1 / -1
inline void FMT_OR(int* a, int n, int op) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < (1 << n); j++)
			if ((1 << i) & j)
				add(a[j], op == 1 ? a[j ^ (1 << i)] : MOD - a[j ^ (1 << i)]);
}
inline void FMT_AND(int* a, int n, int op) {
	for (int i = 0; i < n; i++)
		for (int j = (1 << n) - 1; j >= 0; j--)
			if (!((1 << i) & j))
				add(a[j], op == 1 ? a[j ^ (1 << i)] : MOD - a[j ^ (1 << i)]);
}
const int inv2 = 499122177;
inline void FWT_XOR(int* a, int n, int op) {
	for (int i = 1; i < (1 << n); i <<= 1)
		for (int j = 0; j < (1 << n); j += (i << 1))
			for (int k = 0; k < i; k++) {
				int t = a[j + k];
				a[j + k] = mod1(t + a[i + j + k]);
				a[i + j + k] = mod1(t + MOD - a[i + j + k]);
				if (~op) {
					a[j + k] = 1ll * a[j + k] * inv2 % MOD;
					a[i + j + k] = 1ll * a[i + j + k] * inv2 % MOD;
				}
			}
}