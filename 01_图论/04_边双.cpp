void tarjan(int u, int f) {
	dfn[u] = low[u] = ++tim;
	st[++top] = u;
	for (int v : G[u]) {
		if (v == f) continue;
		if (!dfn[v]) tarjan(v, u), ckmin(low[u], low[v]);
		else ckmin(low[u], dfn[v]);
	}
	if (dfn[u] == low[u]) {
		++totc;
		int x;
		do { x = st[top--], in[x] = 0, bel[x] = totc; } while (x != u);
	}
}
