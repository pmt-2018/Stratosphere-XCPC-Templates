mt19937_64 rnd(time(nullptr));
const ull mask = rnd();
const ull base = rnd();
ull xorshift(ull x) {
	x ^= mask;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= mask;
	return x;
}
ull hsh[maxn], sz[maxn];
void dfs(int u, int f) {
	hsh[u] = base, sz[u] = 1;
	for (int v : G[u]) {
		if (v == f) continue;
		dfs(v, u);
		hsh[u] += xorshift(hsh[v]);
		sz[u] += sz[v];
	}
	hsh[u] += xorshift(sz[u]);
}