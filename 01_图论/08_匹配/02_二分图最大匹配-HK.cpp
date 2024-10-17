// HK, 左到右单向边, O(M \sqrt{|match|})
int nl, nr, m;
vi G[maxn];
int L[maxn], R[maxn], vis[maxn], matchl[maxn], matchr[maxn];
queue<int> Q;
bool bfs() {
	for (int i = 1; i <= nl; i++) L[i] = 0;
	for (int i = 1; i <= nr; i++) R[i] = 0;

	for (int i = 1; i <= nl; i++)
		if (!matchl[i]) L[i] = 1, Q.push(i);
	int succ = 0;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int v : G[u]) {
			if (R[v]) continue;
			R[v] = L[u] + 1;
			if (matchr[v]) {
				L[matchr[v]] = R[v] + 1, Q.push(matchr[v]);
			} else succ = 1;
		}
	}
	return succ;
}
bool dfs(int u) {
	for (int v : G[u])
		if (R[v] == L[u] + 1 && !vis[v]) {
			vis[v] = 1;
			if (!matchr[v] || dfs(matchr[v]))
				return matchl[u] = v, matchr[v] = u, 1;
		}
	return 0;
}
void HK() {
	while (bfs()) {
		for (int i = 1; i <= nr; i++) vis[i] = 0;
		for (int i = 1; i <= nl; ++i)
			if (!matchl[i]) dfs(i);
	}
	return;
}
