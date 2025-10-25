/** @brief 法付き整数型
 * @note デフォルトの法は998244353
 * @note long long mint::default_modを設定することでデフォルトの法を変更できる(0を設定すると998244353になる)
 */
struct mint
{
  private:
    long long n;
    long long mod;

  public:
    static long long default_mod;

	mint() : n(0), mod(default_mod == 0 ? 998244353 : default_mod) {}
    mint(const mint &m) {
        n = m.n;
        mod = m.mod;
    }
    mint(long long n, long long mod = default_mod) {
        if (default_mod == 0) {
			default_mod = mod == 0 ? 998244353 : mod;
			mod = default_mod;
		}
        assert(1 <= mod);

        this->n = (n % mod + mod) % mod;
        this->mod = mod;
    }

	/** @brief 法がmodのときの逆元 O(log mod)
	 * @attention nとmodが互いに素である必要がある
	 */
    mint inv() const {
        assert(gcd(n, mod) == 1);
        auto ext_gcd = [&](auto f, long long a, long long b, long long &x, long long &y) -> long long {
            if (b == 0) {
                x = 1;
                y = 0;
                return a;
            }
            long long d = f(f, b, a % b, y, x);
            y -= a / b * x;
            return d;
        };

        long long x, y;
        ext_gcd(ext_gcd, n, mod, x, y);
        return mint((x % mod + mod) % mod, mod);
    }

	/** @brief 繰り返し2乗法でthisのexp乗 % modを求める O(log exp)
	 * @note expが負のときはthisの法がmodの時の逆元を求める
	 * @attention expが負のときはthis^expがmodと互いに素である必要がある
	 * */
    mint pow(long long exp) const {
        bool inverse = exp < 0;
        if (inverse) exp = -exp;

		ll a = n;
        ll res = 1;
        while (exp > 0) {
            if (exp & 1) res = res * a % mod;
            a = a * a % mod;
            exp >>= 1;
        }
        return (inverse ? mint(res, mod).inv() : mint(res, mod));
    }

	mint &operator=(const mint &o) {
		n = o.n;
		mod = o.mod;
		return *this;
	}

	mint operator+() const { return *this; }
	mint operator-() const { return 0 - *this; }

	mint &operator++() {
		n++;
		if (n == mod) n = 0;
		return *this;
	}
	mint &operator--() {
		if (n == 0) n = mod;
		n--;
		return *this;
	}
	mint operator++(int) {
		mint res = *this;
		++*this;
		return res;
	}
	mint operator--(int) {
		mint res = *this;
		--*this;
		return res;
	}

    mint &operator+=(const mint &o) {
        assert(mod == o.mod);
        n += o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator-=(const mint &o) {
        assert(mod == o.mod);
        n += mod - o.n;
        if (n >= mod) n -= mod;
        return *this;
    }
    mint &operator*=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.n % mod;
        return *this;
    }
    mint &operator/=(const mint &o) {
        assert(mod == o.mod);
        n = n * o.inv().n % mod;
        return *this;
    }
    friend mint operator+(const mint &a, const mint &b) {
        return mint(a) += b;
    }
    friend mint operator-(const mint &a, const mint &b) {
        return mint(a) -= b;
    }
    friend mint operator*(const mint &a, const mint &b) {
        return mint(a) *= b;
    }
    friend mint operator/(const mint &a, const mint &b) {
        return mint(a) /= b;
    }

	friend bool operator==(const mint &a, const mint &b) {
		return a.n == b.n && a.mod == b.mod;
	}
	friend bool operator!=(const mint &a, const mint &b) {
		return a.n != b.n || a.mod != b.mod;
	}

    friend ostream &operator<<(ostream &os, const mint &m) {
        os << m.n;
        return os;
    }
};
long long mint::default_mod = 0;
