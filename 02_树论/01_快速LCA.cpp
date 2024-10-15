// ---
// 查询$[dfn_u + 1 , dfn_v]$深度最小节点的父亲\\
// 可以简化为在 ST 表的最底层记录父亲，比较时取时间戳较小的结点。\\
// 取决于st表实现可以做到$O(n)$ or $O(n\log n)$
// ---
int getmin(int x, int y) {return dfn[x] < dfn[y] ? x : y;}

void dfs(int u, int f) {
    dfn[u] = ++tim;
    a[dfn[u]] = f;
    for(int v : e[u]) if(v != f) dfs(v, u); 
}
int lca(int u, int v) {
    if(u == v) return u;
    if((u = dfn[u]) > (v = dfn[v])) swap(u, v);
    return RMQ(dfn[u] + 1, dfn[v]);
}