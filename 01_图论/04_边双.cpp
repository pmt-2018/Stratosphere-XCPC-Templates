// etot should be initialized to 1 !!!
void tarjan(int u, int f) {
    dfn[u] = low[u] = ++tim;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == f) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            ckmin(low[u], low[v]);
            if (low[v] > dfn[u]) vis[i] = vis[i ^ 1] = 1;  // cut edge
        } else
            ckmin(low[u], dfn[v]);
    }
}
