// 背包大小上界为 m，复杂度为 O(nm)
void solve(int u) {
	sz[u] = 1;
	for (int v : G[u]) {
		solve(v);
		for (int i = 0; i <= m; i++) tmp[i] = 0;
		for (int i = 0; i <= min(m, sz[u]); i++)
			for (int j = 0; j <= min(m - i, sz[v]); j++)
				update(tmp[i + j], dp[u][i], dp[v][j]);
		sz[u] += sz[v];  // DON'T MOVE THIS!!!
		for (int i = 0; i <= m; i++) dp[u][i] = tmp[i];
	}
}