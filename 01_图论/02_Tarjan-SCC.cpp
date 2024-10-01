void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    in[u] = 1;
    st[++top] = u;
    for (int v : G[u]) {
        if (!dfn[v])
            tarjan(v), ckmin(low[u], low[v]);
        else if (in[v])
            ckmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++totc;
        int x;
        do { x = st[top--], in[x] = 0, bel[x] = totc; } while (x != u);
    }
}