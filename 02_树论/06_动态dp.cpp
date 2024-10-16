/*
Problem : Problem
Date : Date
Solver : pmt2018
*/

#include <bits/stdc++.h>

#define y0 pmtx
#define y1 pmtxx
#define x0 pmtxxx
#define x1 pmtxxxx
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lowbit(x) (x & (-x))

#define DEBUG \
	printf("Passing Line %d in function [%s].\n", __LINE__, __FUNCTION__)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;

namespace FastIO {
	const int SIZE = (1 << 20);
	char in[SIZE], *inS = in, *inT = in + SIZE;
	inline char Getchar() {
		if (inS == inT) {
			inT = (inS = in) + fread(in, 1, SIZE, stdin);
			if (inS == inT) return EOF;
		}
		return *inS++;
	}
	char out[SIZE], *outS = out, *outT = out + SIZE;
	inline void Flush() {
		fwrite(out, 1, outS - out, stdout);
		outS = out;
	}
	inline void Putchar(char c) {
		*outS++ = c;
		if (outS == outT) Flush();
	}
	struct NTR {
		~NTR() {
			Flush();
		}
	} ZTR;
}  // namespace FastIO

#ifndef LOCAL
#define getchar FastIO::Getchar
#define putchar FastIO::Putchar
#endif

template <typename T> inline void read(T& x) {
	x = 0;
	int f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
	x *= f;
}

inline void readstr(char* str) {
	int len = 0;
	char c = getchar();
	while (c == ' ' || c == '\n') c = getchar();
	while (c != ' ' && c != '\n' && c != '\r') str[len++] = c, c = getchar();
	str[len] = '\0';
}

template <typename T> inline void write(T x) {
	if (!x) putchar('0');
	if (x < 0) x = -x, putchar('-');
	static int sta[20];
	int tot = 0;
	while (x) sta[tot++] = x % 10, x /= 10;
	while (tot) putchar(sta[--tot] + 48);
}

inline void writestr(char* str) {
	int cur = 0;
	while (str[cur]) putchar(str[cur++]);
}

const int maxn = 500007, INF = 0x3f3f3f3f;
const ll MOD = 998244353;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ll P = 19260817;

template <typename T> inline void ckmax(T& x, T y) {
	x = (y > x ? y : x);
}
template <typename T> inline void ckmin(T& x, T y) {
	x = (y < x ? y : x);
}
template <typename T> inline T my_abs(T x) {
	if (x < 0) x = -x;
	return x;
}
inline int mod1(int x) {
	return x < MOD ? x : x - MOD;
}
inline int mod2(int x) {
	return x < 0 ? x + MOD : x;
}
inline void add(int& x, int y) {
	x = mod1(x + y);
}
inline void sub(int& x, int y) {
	x = mod2(x - y);
}

struct Matrix {
	int mat[2][2];

	Matrix() {
		memset(mat, 0, sizeof mat);
	}

	inline Matrix operator*(Matrix b) {
		Matrix c;

		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j)
				for (int k = 0; k < 2; ++k)
					c.mat[i][j] =
					    mod1(c.mat[i][j] + 1ll * mat[i][k] * b.mat[k][j] % MOD);

		return c;
	}
	void print() {

		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 2; ++j) printf("%d ", mat[i][j]);
		printf("\n");
	}
};

int n;
int sz[maxn];
int A[maxn];
int fa[maxn];
vector<int> G[maxn];
int son[maxn], dfn[maxn], top[maxn], siz[maxn], dep[maxn], id[maxn];
int tim;

void dfs1(int u) {
	siz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for (int v : G[u]) {
		dfs1(v);
		siz[u] += siz[v];
		if (siz[v] > siz[son[u]]) son[u] = v;
	}
}

int endc[maxn];
int F[maxn][2];
Matrix trans[maxn];

struct SegTree2 {
	vector<int> t;
	void init(int sz) {
		t.resize((sz << 2) + 1);
		for (int i = 1; i <= (sz << 2); i++) { t[i] = 1; }
	}
	void pushup(int u) {
		t[u] = 1ll * t[u << 1] * t[u << 1 | 1] % MOD;
	}
	void update(int u, int l, int r, int x, int val) {
		if (l == r) {
			t[u] = val;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid)
			update(u << 1, l, mid, x, val);
		else
			update(u << 1 | 1, mid + 1, r, x, val);
		pushup(u);
	}
} Tson[maxn];

int bel[maxn];

void dfs2(int u, int t) {
	id[u] = ++tim;
	dfn[tim] = u;
	top[u] = t;
	endc[t] = max(endc[t], tim);
	F[u][0] = 0, F[u][1] = 1;
	if (G[u].empty()) {
		F[u][0] = A[u];
		trans[u].mat[0][0] = A[u];
		trans[u].mat[0][1] = 0;
		trans[u].mat[1][0] = 1;
		trans[u].mat[1][1] = 0;
		return;
	}

	Tson[u].init(G[u].size());
	trans[u].mat[0][0] = 1;
	trans[u].mat[0][1] = A[u];
	trans[u].mat[1][0] = 0;
	trans[u].mat[1][1] = 1;
	if (son[u]) {
		dfs2(son[u], t);
		// TODO
	}
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		bel[v] = i + 1;

		if (v == son[u]) continue;
		dfs2(v, v);
		Tson[u].update(1, 1, G[u].size(), bel[v], F[v][0]);
		trans[u].mat[0][0] = 1ll * trans[u].mat[0][0] * F[v][0] % MOD;
	}

	F[u][0] = mod1(A[u] + 1ll * F[son[u]][0] * trans[u].mat[0][0] % MOD);

	// printf("INIT: %d %d\n", u, F[u][0]);
}

struct SegTree {
	Matrix t[maxn << 2];
	void pushup(int u) {
		t[u] = t[u << 1] * t[u << 1 | 1];
	}
	void update(int u, int l, int r, int x) {
		if (l == r) {
			t[u] = trans[dfn[x]];
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid)
			update(u << 1, l, mid, x);
		else
			update(u << 1 | 1, mid + 1, r, x);
		pushup(u);
	}
	Matrix query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) { return t[u]; }
		int mid = (l + r) >> 1;
		if (L > mid) {
			return query(u << 1 | 1, mid + 1, r, L, R);
		} else if (R <= mid) {
			return query(u << 1, l, mid, L, R);
		} else {
			return query(u << 1, l, mid, L, R)
			       * query(u << 1 | 1, mid + 1, r, L, R);
		}
	}
} T;

void update_path(int u, int w) {
	if (G[u].empty()) {
		trans[u].mat[0][0] = w;
		A[u] = w;
	} else {
		trans[u].mat[0][1] = w;
		A[u] = w;
	}

	Matrix bef, aft;
	while (u != 0) {
		// 计算贡献时，应当用一个 bef 矩阵还原出少掉这个轻儿子的情况，再将 aft
		// 加入更新
		T.update(1, 1, n, id[u]);
		aft = T.query(1, 1, n, id[top[u]], endc[top[u]]);
		// printf("%d %d %d\n",top[u], id[top[u]], endc[top[u]]);
		int v = top[u];
		// printf("QUERY %d %d\n", v, aft.mat[0][0]);

		u = fa[v];
		if (u) Tson[u].update(1, 1, G[u].size(), bel[v], aft.mat[0][0]);

		if (u) trans[u].mat[0][0] = Tson[u].t[1];
	}
}

int main() {
#ifdef LOCAL
	// freopen(".in","r",stdin);
	// freopen(".in","w",stdout);
#else
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
#endif
	int Q;
	read(n), read(Q);
	for (int i = 2; i <= n; i++) {
		read(fa[i]);
		G[fa[i]].push_back(i);
	}
	for (int i = 1; i <= n; i++) { read(A[i]); }
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		// trans[i].print();
		T.update(1, 1, n, i);
	}
	while (Q--) {
		int v, x;
		read(v);
		read(x);
		update_path(v, x);
		printf("%d\n", T.query(1, 1, n, id[1], endc[1]).mat[0][0]);
	}
	return 0;
}
