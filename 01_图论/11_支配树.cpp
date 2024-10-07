// ---
// DAG支配树
// ---
namespace DomTree_DAG {
    int idom[maxn];
    vector<int> G[maxn], ANS[maxn];  // ANS: final tree
    int deg[maxn];
    int fa[maxn][25], dep[maxn];
    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = 20; i >= 0; i--)
            if (fa[x][i] && dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if (x == y) return x;
        for (int i = 20; i >= 0; i--)
            if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
        return fa[x][0];
    }
    void work() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            ANS[idom[x]].push_back(x);
            fa[x][0] = idom[x];
            dep[x] = dep[idom[x]] + 1;
            for (int i = 1; i <= 20; i++) fa[x][i] = fa[fa[x][i - 1]][i - 1];
            for (int v : G[x]) {
                --deg[v];
                if (!deg[v]) q.push(v);
                if (!idom[v])
                    idom[v] = x;
                else
                    idom[v] = lca(idom[v], x);
            }
        }
    }
}  // namespace DomTree_DAG
