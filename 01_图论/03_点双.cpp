int T;  // assign = n
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tim;
    stk[++top] = u;
    for (int v : G[u]) {
        if (v == fa) continue;
        if (!dfn[v])
            dfs(v, u), ckmin(low[u], low[v]);
        else
            ckmin(low[u], dfn[v]);
    }
    if (fa && low[u] >= dfn[fa]) {
        int y;
        ++T;
        do {
            y = stk[top--];
            G2[T].push_back(y), G2[y].push_back(T);
        } while (y != u);
        G2[T].push_back(fa), G2[fa].push_back(T);
    }
}