// ---
// DAG支配树
// ---

namespace Dom_DAG {
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
namespace Dom {
	vector<int> G[maxn], rG[maxn];
	int dfn[maxn], id[maxn], anc[maxn], cnt;
	void dfs(int x) {
		id[dfn[x] = ++cnt] = x;
		for (int v : G[x])
			if (!dfn[v]) {
				Dom_DAG::G[x].push_back(v);
				Dom_DAG::deg[v]++;
				anc[v] = x;
				dfs(v);
			}
	}
	int fa[maxn], mn[maxn];
	int find(int x) {
		if (x == fa[x]) return x;
		int tmp = fa[x];
		fa[x] = find(fa[x]);
		ckmin(mn[x], mn[tmp]);
		return fa[x];
	}
	int semi[maxn];
	void work() {
		dfs(1);
		for (int i = 1; i <= n; i++) fa[i] = i, mn[i] = 1e9, semi[i] = i;
		for (int w = n; w >= 2; w--) {
			int x = id[w];
			int cur = 1e9;
			if (w > cnt) continue;
			for (int v : rG[x]) {
				if (!dfn[v]) continue;
				if (dfn[v] < dfn[x])
					ckmin(cur, dfn[v]);
				else
					find(v), ckmin(cur, mn[v]);
			}
			semi[x] = id[cur];
			mn[x] = cur;
			fa[x] = anc[x];
			Dom_DAG::G[semi[x]].push_back(x);
			Dom_DAG::deg[x]++;
		}
	}
	void link(int x, int y) {
		G[x].push_back(y), rG[y].push_back(x);
	}
}  // namespace DomTree