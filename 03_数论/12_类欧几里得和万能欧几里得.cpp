// ---
// 未验证，待补充
// 板子为直线下点数：
// $$ans = \sum_{i=1}^{n-1}\lfloor\frac{ai+b}{m}\rfloor $$
// ---
ull floor_sum(ull n, ull m, ull a, ull b) {
	ull ans = 0;
	while (true) {
		if (a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
		if (b >= m) ans += n * (b / m), b %= m;
		ull ymax = a * n + b;  // use u128 if it's big
		if (ymax < m) break;
		n = ymax / m;
		b = ymax % m;
		std::swap(m, a);
	}
	return ans;
}