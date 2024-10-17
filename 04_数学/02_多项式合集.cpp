// ---
// 务必记得\texttt{Init(n)}在进行多项式乘法前！！！
// ---
const int MOD = 998244353;
const int N = 20;
const int G = 3;
const int MAXN = 3e5 + 5;
typedef vector<int> poly;
void print(const poly& a) {
	for (int i = 0; i < (int)a.size(); i++)
		cout << (i == 0 ? " " : "+ ") << a[i] << "*x^" << i << ' ';
	cout << endl;
}
namespace Poly {
	const int mod = 998244353;
	int rev[MAXN], w[MAXN], wn[N];
	void addmod(int& x, int y) {
		x += y;
		if (x >= mod) x -= mod;
	}
	void submod(int& x, int y) {
		x -= y;
		if (x < 0) x += mod;
	}
	int add(int x, int y) {
		addmod(x, y);
		return x;
	}
	int sub(int x, int y) {
		submod(x, y);
		return x;
	}
	int power(int x, int y) {
		int res = 1;
		while (y) {
			if (y & 1) res = (ll)res * x % mod;
			x = (ll)x * x % mod;
			y >>= 1;
		}
		return res;
	}
	int Inv(int x) { return power(x, mod - 2); }
	void InitNTT(int n) {
		wn[n] = power(G, (mod - 1) / (1 << n));
		for (int i = n - 1; i >= 0; i--)
			wn[i] = (ll)wn[i + 1] * wn[i + 1] % mod;
	}
	int Init(int n) {
		int len = 1;
		while (len < n) len <<= 1;
		for (int i = 0; i < len; i++)
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (len >> 1));
		for (int i = 1, t = 1; i < len; i <<= 1, t += 1) {
			w[i] = 1;
			for (int j = 1; j < i; j++)
				w[i + j] = (ll)w[i + j - 1] * wn[t] % mod;
		}
		return len;
	}
	void NTT(poly& a, int flag) {
		int n = a.size();
		for (int i = 0; i < n; i++)
			if (i < rev[i]) swap(a[i], a[rev[i]]);
		for (int i = 2; i <= n; i <<= 1) {
			int mid = (i >> 1);
			for (int j = 0; j < n; j += i) {
				for (int k = j; k < j + mid; k++) {
					int x = a[k], y = (ll)a[k + mid] * w[k - j + mid] % mod;
					a[k] = add(x, y);
					a[k + mid] = sub(x, y);
				}
			}
		}
		if (flag == -1) {
			reverse(a.begin() + 1, a.begin() + n);
			int invn = Inv(n);
			for (int i = 0; i < n; i++) a[i] = (ll)a[i] * invn % mod;
		}
	}
	poly PolyAdd(const poly& A, const poly& B) {
		poly res = A;
		for (int i = 0; i < (int)A.size(); i++) addmod(res[i], B[i]);
		return res;
	}
	poly PolyMul(const poly& A, const poly& B, int need = 0) {
		int n = A.size(), m = B.size();
		if (n < 5 || m < 5) {
			poly a;
			a.resize(n + m - 1);
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					addmod(a[i + j], (ll)A[i] * B[j] % mod);
			if (need) a.resize(need);
			return a;
		}
		int len = Init(n + m);
		poly a = A, b = B;
		a.resize(len), b.resize(len);
		NTT(a, 1);
		NTT(b, 1);
		for (int i = 0; i < len; i++) a[i] = (ll)a[i] * b[i] % mod;
		NTT(a, -1);
		a.resize(need ? need : n + m - 1);
		return a;
	}
	poly PolyInv(const poly& A) {
		int n = A.size();
		if (n == 1) { return {Inv(A[0])}; }
		poly a = A, b = PolyInv(poly(A.begin(), A.begin() + ((n + 1) >> 1)));
		int len = Init(n << 1);
		a.resize(len), b.resize(len);
		NTT(a, 1);
		NTT(b, 1);
		for (int i = 0; i < len; i++)
			b[i] = (ll)sub(2, (ll)a[i] * b[i] % mod) * b[i] % mod;
		NTT(b, -1);
		b.resize(n);
		return b;
	}
	poly PolyDeriv(const poly& A) {
		int n = A.size();
		poly a = A;
		for (int i = 1; i < n; i++) a[i - 1] = (ll)i * A[i] % mod;
		a[n - 1] = 0;
		return a;
	}
	poly PolyInter(const poly& A) {
		int n = A.size();
		poly a = A;
		for (int i = 1; i < n; i++)
			a[i] = (ll)A[i - 1] * power(i, mod - 2) % mod;
		a[0] = 0;
		return a;
	}
	pair<poly, poly> PolyMod(const poly& A, const poly& B) {
		int n = A.size(), m = B.size();
		if (n < m) return make_pair(poly(1), A);
		poly a = A, b = B;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		b.resize(n - m + 1);
		b = PolyInv(b);
		a.resize(n - m + 1);
		a = PolyMul(a, b, n - m + 1);
		reverse(a.begin(), a.end());
		b = PolyMul(a, B, m - 1);
		for (int i = 0; i < m - 1; i++) b[i] = sub(A[i], b[i]);
		return make_pair(a, b);
	}
	poly PolyLn(const poly& A) {
		int n = A.size();
		poly a = A;
		for (int i = 1; i < n; i++) a[i - 1] = (ll)i * A[i] % mod;
		a[n - 1] = 0;
		a = PolyMul(a, PolyInv(A), n);
		for (int i = n - 1; i >= 1; i--)
			a[i] = (ll)a[i - 1] * power(i, mod - 2) % mod;
		a[0] = 0;
		return a;
	}
	poly PolyExp(const poly& A) {
		int n = A.size();
		if (n == 1) return {1};
		poly b = PolyExp(poly(A.begin(), A.begin() + ((n + 1) >> 1)));
		b.resize(n);
		poly c = PolyLn(b);
		for (int i = 0; i < n; i++) c[i] = sub(A[i], c[i]);
		addmod(c[0], 1);
		poly d = PolyMul(b, c, n);
		return d;
	}
	poly PolyPow(const poly& A, int k) {
		int n = A.size();
		poly a;
		a.resize(n);
		if (!k) {
			a[0] = 1;
			return a;
		}
		int p = 0;
		while (p < n && !A[p]) p += 1;
		if ((ll)p * k >= n) return a;
		int m = n - p * k;
		a.resize(m);
		int coef = power(A[p], k), icoef = power(A[p], mod - 2);
		for (int i = 0; i < m; i++) a[i] = (ll)A[i + p] * icoef % mod;
		a = PolyLn(a);
		for (int i = 0; i < m; i++) a[i] = (ll)a[i] * k % mod;
		a = PolyExp(a);
		poly b;
		b.resize(n);
		for (int i = 0; i < m; i++) b[i + p * k] = (ll)a[i] * coef % mod;
		return b;
	}
	poly tmp[MAXN];
#define lson k << 1
#define rson k << 1 | 1
	void pre_eval(const poly& A, int k, int l, int r) {
		if (l == r) {
			tmp[k].resize(2);
			tmp[k][0] = sub(0, A[l]);
			tmp[k][1] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		pre_eval(A, lson, l, mid);
		pre_eval(A, rson, mid + 1, r);
		tmp[k] = PolyMul(tmp[lson], tmp[rson]);
	}
	void solve_eval(const poly& A, const poly& B, poly& C, int k, int l,
	                int r) {
		if (r - l <= 30) {
			for (int i = l; i <= r; i++)
				for (int j = A.size() - 1; j >= 0; j--)
					C[i] = (A[j] + (ll)C[i] * B[i] % mod) % mod;
			return;
		}
		int mid = (l + r) >> 1;
		solve_eval(PolyMod(A, tmp[lson]).second, B, C, lson, l, mid);
		solve_eval(PolyMod(A, tmp[rson]).second, B, C, rson, mid + 1, r);
	}
	poly PolyEval(const poly& A, const poly& B) {
		int m = B.size();
		pre_eval(B, 1, 0, m - 1);
		poly c;
		c.resize(m);
		solve_eval(PolyMod(A, tmp[1]).second, B, c, 1, 0, m - 1);
		return c;
	}
	poly solve_itpl(const poly& A, int k, int l, int r) {
		if (l == r) return {A[l]};
		int mid = (l + r) >> 1;
		return PolyAdd(PolyMul(solve_itpl(A, lson, l, mid), tmp[rson]),
		               PolyMul(solve_itpl(A, rs on, mid + 1, r), tmp[lson]));
	}
	poly PolyItpl(const poly& A, const poly& B) {
		int n = A.size();
		pre_eval(A, 1, 0, n - 1);
		poly a;
		a.resize(n);
		solve_eval(PolyDeriv(tmp[1]), A, a, 1, 0, n - 1);
		for (int i = 0; i < n; i++) a[i] = (ll)B[i] * Inv(a[i]) % MOD;
		return solve_itpl(a, 1, 0, n - 1);
	}
#undef lson
#undef rson
	struct Initializer {
		Initializer() { InitNTT(N - 1); }
	} initializer;
}  // namespace Poly