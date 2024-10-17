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
Vector dp[maxn];  // F[u] 为 u 的 dp 值
Matrix trans[maxn];
// 考虑u点所有轻儿子以及u点点权的贡献转移矩阵，则某点u的dp值为 trans[u]*dp[son[u]]
void dfs2(int u, int t) {
	dfn[u] = ++tim, id[tim] = u;
	top[u] = t, endc[t] = max(endc[t], tim);
	// TODO: 初始化 F[u] 和 trans[u]
	if (son[u]) dfs2(son[u], t);
	for (int v : G[u]) {
		if (v == son[u]) continue;
		dfs2(v, v);
		// TODO: 用 dp[v] 更新 trans[u]
	}
	dp[u] = trans[u] * dp[son[u]];
}

struct Segtree {
	Matrix t[maxn << 2];
	void build(int u, int l, int r);  // t[u] = trans[id[x]];
	void pushup(int u);
	void update(int u, int l, int r, int x);  // t[u] = trans[id[x]]
	Matrix query(int u, int l, int r, int L, int R);
} T;

void update(int u) {
	// TODO: 更新 trans[u] 和 dp[u]
	Matrix aft;
	while (u != 0) {
		T.update(1, 1, n, dfn[u]);
		aft = T.query(1, 1, n, dfn[top[u]], endc[top[u]]);
		int v = top[u];
		u = fa[v];
		if (u) {}  // TODO: 用 aft 更新 trans[u] 和 dp[u]
	}
}
Vector query() { return T.query(1, 1, n, id[1], endc[1]) * dp[id[endc[1]]]; }