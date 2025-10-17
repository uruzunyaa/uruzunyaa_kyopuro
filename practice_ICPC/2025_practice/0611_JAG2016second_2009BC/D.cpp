#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define rrep(i, n) for(ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 9009009009009009009LL;
constexpr int INF32 = 2002002002;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

// Linear Algebra ////////////////////////////////////////////////
const double Rad2Deg = 180.0 / M_PI;
const double Deg2Rad = M_PI / 180.0;
//////////////////////////////////////////////////////////////////

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

template <class T>
inline bool chmax(T &a, const T &b) {
	if (a < b) {
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmin(T &a, const T &b) {
	if (a > b) {
		a = b;
		return true;
	}
	return false;
}

template <typename Container,
          typename = std::enable_if_t<
              !std::is_same_v<Container, std::string> &&
              std::is_convertible_v<decltype(std::declval<Container>().begin()),
                                    typename Container::iterator>>>
ostream &operator<<(ostream &os, const Container &container) {
    auto it = container.begin();
    auto end = container.end();

    if (it != end) {
        os << *it;
        ++it;
    }
	for (; it != end; ++it) {
		os << " " << *it;
	}
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) os << " ";
    }
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& vv) {
	for (size_t i = 0; i < vv.size(); ++i) {
		os << vv[i];
		if (i != vv.size() - 1) os << "\n";
    }
    return os;
}
template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
	assert(v.size() > 0);
	for (size_t i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (size_t i = 0; i < vv.size(); ++i) is >> vv[i];
	return is;
}

struct phash {
	template<class T1, class T2>
    inline size_t operator()(const pair<T1, T2> & p) const {
        auto h1 = hash<T1>()(p.first);
        auto h2 = hash<T2>()(p.second);

		size_t seed = h1 + h2; 
		h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = ((h1 >> 16) ^ h1) * 0x45d9f3b;
        h1 = (h1 >> 16) ^ h1;
        seed ^= h1 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = ((h2 >> 16) ^ h2) * 0x45d9f3b;
        h2 = (h2 >> 16) ^ h2;
        seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};





int solve() {
	ll n;
	cin >> n;
	if (n == 0)
		return 1;

	vector<PLL> vert(n);
	rep(i, n)
	{
		cin >> vert[i].first >> vert[i].second;
		vert[i].first += 2 * 1e4;
		vert[i].second += 2 * 1e4;
	}
	vector<PLL> cur_vert(4);
	rep(i, 4) {
		 cin >> cur_vert[i].first >> cur_vert[i].second;
		 cur_vert[i].first += 2 * 1e4;
		 cur_vert[i].second += 2 * 1e4;
	}

	vvll bound(4 * 1e4 + 10, vll());
	rep(i, n) {
		auto [x, y] = vert[i];
		auto [nx, ny] = vert[(i + 1) % n];
		if (x == nx)
			continue;
		if (nx < x)
			swap(x, nx);
		loop(j, x, nx - 1) {
			bound[j].push_back(y);
		}
	}

	vvll curtain(4 * 1e4 + 10, vll());
	rep(i, 4) {
		auto [x, y] = cur_vert[i];
		auto [nx, ny] = cur_vert[(i + 1) % 4];
		if (x == nx)
			continue;
		if (nx < x)
			swap(x, nx);
		loop(j, x, nx - 1) {
			curtain[j].push_back(y);
		}
	}

	ll ans = 0;
	rep(i, bound.size()) {
		assert(bound[i].size() % 2 == 0);
		assert(curtain[i].size() == 2 || curtain[i].size() == 0);
		sort(all(bound[i]));
		sort(all(curtain[i]));
		rep(j, bound[i].size() / 2) {
			ll idx = 2 * j;
			if (curtain[i].size() == 2) {
				ll mn = curtain[i][0];
				ll mx = curtain[i][1];
				ans += abs(min(bound[i][idx], mn) - min(bound[i][idx + 1], mn));
				ans += abs(max(bound[i][idx], mx) - max(bound[i][idx + 1], mx));
			}
			else {
				ans += abs(bound[i][idx] - bound[i][idx + 1]);
			}
		}
	}

	cout << ans << "\n";

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) {}
	return 0;
}
