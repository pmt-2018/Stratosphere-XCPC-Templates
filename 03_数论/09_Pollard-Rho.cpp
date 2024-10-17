namespace factor {
	using f64 = long double;
	ll p;
	f64 invp;
	inline void setmod(ll x) { p = x, invp = (f64)1 / x; }
	inline ll mul(ll a, ll b) {
		ll z = a * invp * b + 0.5;
		ll res = a * b - z * p;
		return res + (res >> 63 & p);
	}
	inline ll pow(ll a, ll x, ll res = 1) {
		for (; x; x >>= 1, a = mul(a, a))
			if (x & 1) res = mul(res, a);
		return res;
	}
	inline bool checkprime(ll p) {
		if (p == 1) return 0;
		setmod(p);
		ll d = __builtin_ctzll(p - 1), s = (p - 1) >> d;
		for (ll a : {2, 3, 5, 7, 11, 13, 82, 373}) {
			if (a % p == 0) continue;
			ll x = pow(a, s), y;
			for (int i = 0; i < d; ++i, x = y) {
				y = mul(x, x);
				if (y == 1 && x != 1 && x != p - 1) return 0;
			}
			if (x != 1) return 0;
		}
		return 1;
	}
	inline ll rho(ll n) {
		if (!(n & 1)) return 2;
		static std::mt19937_64 gen((size_t) "hehezhou");
		ll c = gen() % (n - 1) + 1, y = gen() % (n - 1) + 1;
		auto f = [&](ll o) {
			o = mul(o, o) + c;
			return o >= n ? o - n : o;
		};
		setmod(p);
		for (int l = 1;; l <<= 1) {
			ll x = y, g = 1;
			for (int i = 0; i < l; ++i) y = f(y);
			const int d = 512;
			for (int i = 0; i < l; i += d) {
				ll sy = y;
				for (int j = 0; j < min(d, l - i); ++j) {
					y = f(y), g = mul(g, (y - x + n));
				}
				g = gcd(n, g);
				if (g == 1) continue;
				if (g == n)
					for (g = 1, y = sy; g == 1;)
						y = f(y), g = gcd(n, y - x + n);
				return g;
			}
		}
	}
	inline std::vector<ll> factor(ll x) {
		std::queue<ll> q;
		q.push(x);
		std::vector<ll> res;
		for (; q.size();) {
			ll x = q.front();
			q.pop();
			if (x == 1) continue;
			if (checkprime(x)) {
				res.push_back(x);
				continue;
			}
			ll y = rho(x);
			q.push(y), q.push(x / y);
		}
		sort(res.begin(), res.end());
		return res;
	}
}  // namespace factor