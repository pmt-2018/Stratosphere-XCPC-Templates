// ---
// Dinic 算法
// ---
namespace Dinic {
	int N, S, T;
	struct edge {
		int to, nxt, cap;
	} e[maxm << 1];
	int head[maxn], cur[maxn], tot = 1;
	int d[maxn];
	void addedge(int u, int v, int c) {
		e[++tot] = (edge){v, head[u], c}, head[u] = tot;
		e[++tot] = (edge){u, head[v], 0}, head[v] = tot;
	}
	bool bfs(int S, int T) {
		queue<int> q;
		for (int i = 1; i <= N; i++) d[i] = 0;
		d[S] = 1;
		q.push(S);
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (int i = head[u]; i; i = e[i].nxt) {
				int v = e[i].to;
				if (e[i].cap && !d[v]) {
					d[v] = d[u] + 1, q.push(v);
					if (v == T) return true;
				}
			}
		}
		return false;
	}
	int dfs(int u, int f) {
		if (u == T) return f;
		int r = f;
		for (int& i = cur[u]; i && r; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].cap && d[v] == d[u] + 1) {
				int x = dfs(v, min(e[i].cap, r));
				if (!x) d[v] = 0;
				e[i].cap -= x, e[i ^ 1].cap += x;
				r -= x;
			}
		}
		return f - r;
	}
	ll work(int _N, int _S, int _T) {
		N = _N, S = _S, T = _T;
		ll ans = 0;
		while (bfs(S, T)) {
			for (int i = 1; i <= N; i++) cur[i] = head[i];
			ans += 1ll * dfs(S, INF);
		}
		return ans;
	}
}  // namespace Dinic
// ---
// ISAP 算法
// ---
namespace ISAP {
	int N, S, T;
	struct edge {
		int to, nxt, cap;
	} e[maxm << 1];
	int head[maxn], cur[maxn], gap[maxn], dis[maxn], tot = 1;
	void addedge(int u, int v, int w) {
		e[++tot] = {v, head[u], w}, head[u] = tot;
		e[++tot] = {u, head[v], 0}, head[v] = tot;
	}
	int ISAP(int u, int lim) {
		if (u == T) return lim;
		int res = 0;
		for (int& i = cur[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].cap && dis[u] == dis[v] + 1) {
				ll det = ISAP(v, min(lim, e[i].cap));
				e[i].cap -= det, e[i ^ 1].cap += det;
				lim -= det, res += det;
				if (!lim) return res;
			}
		}
		cur[u] = head[u];
		if (!--gap[dis[u]]) dis[S] = N + 1;
		gap[++dis[u]]++;
		return res;
	}
	ll work(int _N, int _S, int _T) {
		S = _S, T = _T, N = _N;
		ll res = 0;
		while (dis[S] <= N) res += 1ll * ISAP(S, INF);
		return res;
	}
}  // namespace ISAP
// ---
// HLPP 算法
// ---
namespace HLPP {  // by ProjectEMmm
	int N, S, T;
	struct edge {
		int to, nxt, cap;
	} e[maxm << 1];
	int head[maxn], tot = 1;

	int d[maxn], num[maxn];
	stack<int> lib[maxn];
	ll ex[maxn];
	int level = 0;
	void addedge(int u, int v, int c) {
		e[++tot] = {v, head[u], c}, head[u] = tot;
		e[++tot] = {u, head[v], 0}, head[v] = tot;
	}
	int Push(int u) {
		bool init = (u == S);
		for (int i = head[u]; i; i = e[i].nxt) {
			const int &v = e[i].to, &c = e[i].cap;
			if (!c || init == false && d[u] != d[v] + 1) continue;
			ll k = init ? c : min((ll)c, ex[u]);
			if (v != S && v != T && !ex[v] && d[v] < INF)
				lib[d[v]].push(v), level = max(level, d[v]);
			ex[u] -= k, ex[v] += k, e[i].cap -= k, e[i ^ 1].cap += k;
			if (!ex[u]) return 0;
		}
		return 1;
	}
	void Relabel(int x) {
		d[x] = INF;
		for (int i = head[x]; i; i = e[i].nxt)
			if (e[i].cap) d[x] = min(d[x], d[e[i].to]);
		if (++d[x] < N) {
			lib[d[x]].push(x);
			level = max(level, d[x]);
			++num[d[x]];
		}
	}
	bool BFS() {
		for (int i = 1; i <= N; ++i) {
			d[i] = INF;
			num[i] = 0;
		}
		queue<int> q;
		q.push(T), d[T] = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			num[d[u]]++;
			for (int i = head[u]; i; i = e[i].nxt) {
				const int& v = e[i].to;
				if (e[i ^ 1].cap && d[v] > d[u] + 1) d[v] = d[u] + 1, q.push(v);
			}
		}
		return d[S] != INF;
	}
	int Select() {
		while (lib[level].size() == 0 && level > -1) level--;
		return level == -1 ? 0 : lib[level].top();
	}
	ll work(int _N, int _S, int _T) {
		N = _N, S = _S, T = _T;
		if (!BFS()) return 0;
		d[S] = N;
		Push(S);
		int x;
		while (x = Select()) {
			lib[level].pop();
			if (!Push(x)) continue;
			if (!--num[d[x]])
				for (int i = 1; i <= N; ++i)
					if (i != S && i != T && d[i] > d[x] && d[i] < N + 1)
						d[i] = N + 1;
			Relabel(x);
		}
		return ex[T];
	}
}  // namespace HLPP