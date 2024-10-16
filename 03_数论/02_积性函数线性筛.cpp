// ---
// 欧拉函数和莫比乌斯函数可以更简单的线性筛，见注释
// ---
bool vis[maxn];
int prime[maxn], totp, mnpe[maxn], f[maxn];
void init() {
	vis[1] = 1;
	mnpe[1] = 1;  // mu[1] = ph[1] = 1
	for (int i = 2; i <= N; i++) {
		if (!vis[i])
			prime[++totp] = i, mnpe[i] = i;  // mu[i] = -1, phi[i] = i - 1;
		for (int j = 1; j <= totp && i * prime[j] <= N; j++) {
			if (i % prime[j] == 0) {
				mnpe[i * prime[j]] = mnpe[i] * prime[j];
				// mu[i * prime[j]] = 0;
				// phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			vis[i * prime[j]] = 1;
			mnpe[i * prime[j]] = prime[j];
			// mu[i * prime[j]] = -mu[i];
			// phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 1; i <= totp; i++)
		for (int e = 1, p = prime[i]; p <= N; e++, p *= prime[i]) {
			// TODO: 在这里计算素数幂处的值 f[p]
		}
	for (int i = 1; i <= N; i++)
		if (i != mnpe[i]) f[i] = f[mnpe[i]] * f[i / mnpe[i]];
}