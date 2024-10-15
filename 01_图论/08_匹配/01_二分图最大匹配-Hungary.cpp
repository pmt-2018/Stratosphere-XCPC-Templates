// 匈牙利,左到右单向边, O (M |match|)
int vis[maxn], match[maxn];
bool dfs(int u) {
	for (int v : G[u]) {
		if (vis[v]) continue;
		vis[v] = 1;
		if (!match[v] || dfs(match[v])) return match[v] = u, 1;
	}
	return 0;
}
int work() {
	for (int i = 1; i <= nl; i++)
		if (dfs(i)) fill(vis + 1, vis + nr + 1, 0);
}
// 匈牙利,左到右单向边,bitset, O (n^2|match|/w)
bitset<N> G[N], unvis;
int match[N];
bool dfs(int u) {
	for (auto s = G[u];;) {
		s &= unvis;
		int v = s._Find_first();
		if (v == N) return 0;
		unvis.reset(v);
		if (!match[v] || dfs(match[v])) return match[v] = u, 1;
	}
	return 0;
}
int work() {
	unvis.set();
	for (int i = 1; i <= nl; i++)
		if (dfs(i)) unvis.set();
}