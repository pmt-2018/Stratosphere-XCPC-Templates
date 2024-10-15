namespace MCMF {
	using pr = pair<ll, int>;
	int N, S, T;
	struct edge {
		int to, nxt, cap, w;
	} e[maxm << 1];
	int head[maxn], tot = 1;
	void addedge(int x, int y, int cap, int w) {
		e[++tot] = {y, head[x], cap, w}, head[x] = tot;
		e[++tot] = {x, head[y], 0, -w}, head[y] = tot;
	}
	ll d[maxn], dis[maxn];
	int vis[maxn], fr[maxn];
	bool spfa() {
		queue<int> Q;
		fill(d + 1, d + N + 1, 1e18);  // CHECK
		for (d[S] = 0, Q.push(S); !Q.empty();) {
			int x = Q.front();
			Q.pop();
			vis[x] = 0;
			for (int i = head[x]; i; i = e[i].nxt)
				if (e[i].cap && d[e[i].to] > d[x] + e[i].w) {
					d[e[i].to] = d[x] + e[i].w;
					fr[e[i].to] = i;
					if (!vis[e[i].to]) vis[e[i].to] = 1, Q.push(e[i].to);
				}
		}
		return d[T] < 1e17;  // 如果只是最小费用流，当d < 0继续增广
	}
	bool dijkstra() {  // 正常题目不需要 dijk
		priority_queue<pr, vector<pr>, greater<pr>> Q;
		for (int i = 1; i <= N; ++i)
			dis[i] = d[i], d[i] = 1e18, vis[i] = fr[i] = 0;  // CHECK
		Q.emplace(d[S] = 0, S);
		while (!Q.empty()) {
			int x = Q.top().second;
			Q.pop();
			if (vis[x]) continue;
			vis[x] = 1;
			for (int i = head[x]; i; i = e[i].nxt) {
				const ll v = e[i].w + dis[x] - dis[e[i].to];
				if (e[i].cap && d[e[i].to] > d[x] + v) {
					fr[e[i].to] = i;
					Q.emplace(d[e[i].to] = d[x] + v, e[i].to);
				}
			}
		}
		for (int i = 1; i <= N; ++i) d[i] += dis[i];  // CHECK
		return d[T] < 1e17;
	}
	std::pair<ll, ll> work(int _N, int _S, int _T) {
		N = _N, S = _S, T = _T;
		spfa();  // 如果初始有负权且要 dijk
		ll f = 0, c = 0;
		for (; dijkstra();) {  // 正常可以用 spfa
			ll fl = 1e18;
			for (int i = fr[T]; i; i = fr[e[i ^ 1].to])
				fl = min((ll)e[i].cap, fl);
			for (int i = fr[T]; i; i = fr[e[i ^ 1].to])
				e[i].cap -= fl, e[i ^ 1].cap += fl;
			f += fl, c += fl * d[T];
		}
		return make_pair(f, c);
	}
}  // namespace MCMF