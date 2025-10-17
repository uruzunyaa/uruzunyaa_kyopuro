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
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n *(n - 1) / 2
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
inline bool chmax(T &a, const T &b)
{
	if (a < b)
	{
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmin(T &a, const T &b)
{
	if (a > b)
	{
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
ostream &operator<<(ostream &os, const Container &container)
{
	auto it = container.begin();
	auto end = container.end();

	if (it != end)
	{
		os << *it;
		++it;
	}
	for (; it != end; ++it)
	{
		os << " " << *it;
	}
	return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		os << v[i];
		if (i != v.size() - 1)
			os << " ";
	}
	return os;
}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &vv)
{
	for (size_t i = 0; i < vv.size(); ++i)
	{
		os << vv[i];
		if (i != vv.size() - 1)
			os << "\n";
	}
	return os;
}
template <typename T>
istream &operator>>(istream &is, vector<T> &v)
{
	assert(v.size() > 0);
	for (size_t i = 0; i < v.size(); ++i)
		is >> v[i];
	return is;
}
template <typename T>
istream &operator>>(istream &is, vector<vector<T>> &vv)
{
	assert(vv.size() > 0);
	for (size_t i = 0; i < vv.size(); ++i)
		is >> vv[i];
	return is;
}

struct phash
{
	template <class T1, class T2>
	inline size_t operator()(const pair<T1, T2> &p) const
	{
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

int solve()
{
	ll h, w;
	cin >> h >> w;
	if (h == 0 && w == 0)
		return 1;
	vector<string> g(h);
	cin >> g;

	const PLL dL1[4] = {{0, 1}, {1, 0}, {0, 1}, {1, 0}};
	const PLL dL2[4] = {{1, 1}, {1, 1}, {1, 0}, {1, -1}};

	ll ans = 0;
	auto dfs = [&](auto dfs, vector<vector<bool>> &filled, ll sy, ll sx) -> void
	{
		while (sy < h && sx < w)
		{
			if (g[sy][sx] == '.' && !filled[sy][sx])
				break;

			sx++;
			if (sx == w)
			{
				sx = 0;
				sy++;
			}
			if (sy == h)
			{
				ans++;
				return;
			}
		}

		rep(rot, 4)
		{
			ll ny1 = sy + dL1[rot].first;
			ll nx1 = sx + dL1[rot].second;
			ll ny2 = sy + dL2[rot].first;
			ll nx2 = sx + dL2[rot].second;

			if (ny1 < 0 || h <= ny1 || nx1 < 0 || w <= nx1)
				continue;
			if (ny2 < 0 || h <= ny2 || nx2 < 0 || w <= nx2)
				continue;
			if (g[ny1][nx1] == '#' || filled[ny1][nx1])
				continue;
			if (g[ny2][nx2] == '#' || filled[ny2][nx2])
				continue;

			filled[sy][sx] = true;
			filled[ny1][nx1] = true;
			filled[ny2][nx2] = true;
			dfs(dfs, filled, sy, sx);
			filled[sy][sx] = false;
			filled[ny1][nx1] = false;
			filled[ny2][nx2] = false;
		}
	};
	vector<vector<bool>> filled(h, vector<bool>(w, false));
	dfs(dfs, filled, 0, 0);

	cout << ans << "\n";

	return 0;
}

int main()
{
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve())
	{
	}
	return 0;
}
