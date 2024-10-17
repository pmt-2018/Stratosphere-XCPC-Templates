gp_hash_table<ll, ll> s;
ll exgcd(ll a, ll b) {
	if (a == 1) return 1;
	return (1 - b * exgcd(b % a, a)) / a;  // not ll
}
ll exBSGS(ll a, ll b, ll p) {
	s.clear();
	a %= p, b %= p;
	ll j = 1 % p, cnt = 0;
	for (int i = 0; i <= __lg(p); i++, j = j * a % p)
		if (j == b) return i;
	ll x, y = 1;
	while (true) {
		x = gcd(a, p);
		if (x == 1) break;
		if (b % x) return -1;  // no sol
		cnt++;
		p /= x, b /= x;
		y = y * (a / x) % p;
	}
	a %= p;
	b = (ll)b * (p + exgcd(y, p)) % p;
	x = ceil(sqrt(p)), j = 1;
	for (int i = 0; i < x; i++, j = j * a % p) {
		if (j == b) return i + cnt;
		s[j * b % p] = i + 1;
	}
	int k = j;
	for (int i = 1; i <= x; i++, j = (ll)j * k % p)
		if (s[j]) return (ll)i * x + cnt - s[j] + 1;
	return -1;
}