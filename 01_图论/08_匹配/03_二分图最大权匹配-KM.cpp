// KM 二分图最大权匹配 复杂度O(n^3)
namespace KM {
	int nl, nr;
	ll e[maxn][maxn], lw[maxn], rw[maxn], mnw[maxn];
	int lpr[maxn], rpr[maxn], vis[maxn], fa[maxn];
	void addedge(int x, int y, ll w) { ckmax(e[x][y], w), ckmax(lw[x], w); }
	void work(int x) {
		int xx = x;
		for (int i = 1; i <= nr; i++) vis[i] = 0, mnw[i] = 1e18;
		while (true) {
			for (int i = 1; i <= nr; i++)
				if (!vis[i] && mnw[i] >= lw[x] + rw[i] - e[x][i])
					ckmin(mnw[i], lw[x] + rw[i] - e[x][i]), fa[i] = x;
			ll mn = 1e18;
			int y = -1;
			for (int i = 1; i <= nr; i++)
				if (!vis[i] && mn >= mnw[i]) ckmin(mn, mnw[i]), y = i;
			lw[xx] -= mn;
			for (int i = 1; i <= nr; i++)
				if (vis[i]) rw[i] += mn, lw[rpr[i]] -= mn;
				else mnw[i] -= mn;
			if (rpr[y]) x = rpr[y], vis[y] = 1;
			else {
				while (y) rpr[y] = fa[y], swap(y, lpr[fa[y]]);
				return;
			}
		}
	}
	void init(int _nl, int _nr) {
		nl = _nl, nr = _nr;
		if (nl > nr) nr = nl;
		for (int i = 1; i <= nl; i++) lw[i] = -1e18;
		for (int i = 1; i <= nl; i++)
			for (int j = 1; j <= nr; j++) e[i][j] = 0;  // or -1e18
	}
	ll work() {
		for (int i = 1; i <= nl; i++) work(i);
		ll tot = 0;
		for (int i = 1; i <= nl; i++) tot += e[i][lpr[i]];
		return tot;
	}
}  // namespace KM