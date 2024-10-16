// ---
// \noindent 构造方案时可以通过变量在图中的拓扑序确定该变量的取值。\\
// 如果变量$x$的拓扑序在$\lnot x$之后,那么取$x$值为真。\\
// 因为Tarjan 算法求强连通分量时使用了栈,所以 Tarjan 求得的 SCC
// 编号相当于反拓扑序。
// ---
for (int i = 1; i <= n; i++)
	if (bel[i << 1] == bel[i << 1 | 1]) return puts("IMPOSSIBLE"), 0;
puts("POSSIBLE");
for (int i = 1; i <= n; i++) printf("%d ", bel[i << 1] > bel[i << 1 | 1]);