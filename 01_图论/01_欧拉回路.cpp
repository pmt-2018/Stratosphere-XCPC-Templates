namespace Euler {
    bool directed;
    vector<pii> G[maxn];
    vector<int> ans;
    int vis[maxm];
    int dfs(int x) {
        vector<int> t;
        while (G[x].size()) {
            auto [to, id] = G[x].back();
            G[x].pop_back();
            if (!vis[abs(id)]) {
                vis[abs(id)] = 1, t.push_back(dfs(to)), ans.push_back(id);
            }
        }
        for (int i = 1; i < t.size(); i++) {
            if (t[i] != x) ans.clear();
        }
        return t.size() ? t[0] : x;
    }
    int n, m;
    pii e[maxm];
    int deg[maxn], vv[maxn];
    void clr() {
        for (int i = 1; i <= n; i++) G[i].clear(), deg[i] = vv[i] = 0;
        for (int i = 1; i <= m; i++) vis[i] = 0;
        ans.clear();
        n = m = 0;
    }
    void addedge(int x, int y) {
        chkmax(n, x), chkmax(n, y);
        ++m;
        e[m] = {x, y};
        if (directed) {
            G[x].push_back({y, m});
            ++deg[x], --deg[y], vv[x] = vv[y] = 1;
        } else {
            G[x].push_back({y, m});
            G[y].push_back({x, -m});
            ++deg[x], ++deg[y], vv[x] = vv[y] = 1;
        }
    }
    using vi = vector<int>;
    pair<vi, vi> work() {
        if (!m) return clr(), pair<vi, vi>{{1}, {}};
        int S = 1;
        for (int i = 1; i <= n; i++)
            if (vv[i]) S = i;
        for (int i = 1; i <= n; i++)
            if (deg[i] > 0 && deg[i] % 2 == 1) S = i;
        dfs(S);
        if ((int)ans.size() != m) return clr(), pair<vi, vi>();
        reverse(ans.begin(), ans.end());
        vi ver, edge = ans;
        if (directed) {
            ver = {e[ans[0]].fir};
            for (auto t : ans) ver.push_back(e[t].sec);
        } else {
            ver = {ans[0] > 0 ? e[ans[0]].fir : e[-ans[0]].sec};
            for (auto t : ans) ver.push_back(t > 0 ? e[t].sec : e[-t].fir);
        }
    }
}  // namespace Euler