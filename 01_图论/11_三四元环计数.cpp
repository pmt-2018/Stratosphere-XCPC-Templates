static int id[maxn], rnk[maxn];
for (int i = 1; i <= n; i++) id[i] = i;
sort(id + 1, id + n + 1, [](int x, int y) {
	return pii{deg[x], x} < pii{deg[y], y};
});
for (int i = 1; i <= n; i++) rnk[id[i]] = i;
for (int i = 1; i <= n; i++)
	for (int v : G[i])
		if (rnk[v] > rnk[i]) G2[i].push_back(v);
int ans3 = 0;  // 3-cycle
for (int i = 1; i <= n; i++) {
	static int vis[maxn];
	for (int v : G2[i]) vis[v] = 1;
	for (int v1 : G2[i])
		for (int v2 : G2[v1])
			if (vis[v2]) ++ans3;  // (i,v1,v2)
	for (int v : G2[i]) vis[v] = 0;
}
ll ans4 = 0;  // 4-cycle
for (int i = 1; i <= n; i++) {
	static int vis[maxn];
	for (int v1 : G[i])
		for (int v2 : G2[v1])
			if (rnk[v2] > rnk[i]) ans4 += vis[v2], vis[v2]++;
	for (int v1 : G[i])
		for (int v2 : G2[v1]) vis[v2] = 0;
}