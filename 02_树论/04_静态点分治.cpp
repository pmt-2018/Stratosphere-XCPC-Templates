void get_root(int u, int f) {
	sz[u] = 1, wt[u] = 0;
	for (int v : G[u]) {
		if (v == f || vis[v]) continue;
		get_root(v, u), sz[u] += sz[v], ckmax(wt[u], sz[v]);
	}
	ckmax(wt[u], Tsize - sz[u]);
	if (wt[Rt] > wt[u]) Rt = u;
}
void solve(int u) {
	vis[u] = 1;
	for (int v : G[u]) {
		if (vis[v]) continue;
		Rt = 0, Tsize = sz[v], get_root(v, 0);
		solve(Rt);
	}
}
wt[Rt = 0] = INF, Tsize = n;
get_root(1, 0);
solve(Rt);