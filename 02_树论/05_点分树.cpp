// ---
// 待验证，以下为领域点权和模版
// ---
void build(int u) {
	vis[u] = 1;
	t2[u].add(0, a[u]);
	for (int v : G[u]) {
		if (vis[v]) continue;
		Rt = 0, mxdep = 0, Tsize = sz[v];
		get_root(v, 0, 1);
		fa[Rt] = u;
		t1[Rt].init(mxdep + 5);
		t2[Rt].init(mxdep + 5);
		get_dis(v, u, 1);
		build(Rt);
	}
}
void modify(int u, int val) {
	for (int i = u; i; i = fa[i]) {
		t2[i].add(dis(u, i), val - a[u]);
		if (fa[i]) t1[i].add(dis(u, fa[i]), val - a[u]);
	}
	a[u] = val;
}
int query(int u, int k) {
	int rt = 0;
	for (int i = u; i; i = fa[i]) {
		rt += t2[i].query(k - dis(u, i));
		if (fa[i]) rt -= t1[i].query(k - dis(u, fa[i]));
	}
	return rt;
}