vector<int> Gn[maxn];
int st[maxn], top;
void build(vector<int> v) {
	sort(v.beign(), v.end(),
	     [&](const int& a, const int& b) { return dfn[a] < dfn[b]; });
	top = 0;
	if (v[0] != 1) st[++top] = 1;  // Assume 1 is the root
	for (int u : v) {
		if (!top) {
			st[++top] = u;
			continue;
		}
		int anc = lca(st[top], u);
		if (anc == st[top]) {
			st[++top] = u;
			continue;
		}
		while (top > 1 && dfn[lca] <= dfn[st[top - 1]]) {
			Gn[st[top - 1]].pb(st[top]), top--;
		}
		if (anc != st[top]) Gn[anc].pb(st[top]), st[top] = anc;
		st[++top] = u;
	}
	while (top) Gn[st[top - 1]].pb(st[top]), top--;
}
// use DFS to clear Gn