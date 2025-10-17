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

	PLL s, g;
	cin >> s.second >> s.first >> g.second >> g.first;

	const ll GSIZE = 1100;
	const ll CONSTRAINT = 1000;

	bool inverseX = false;
	if (g.first < s.first)
		swap(s, g);
	if (g.second < s.second) {
		inverseX = true;
		s.second = CONSTRAINT + 1 - s.second;
		g.second = CONSTRAINT + 1 - g.second;
	}

	vvll imosx(GSIZE, vll(GSIZE, 0));
	vvll imosy(GSIZE, vll(GSIZE, 0));

	ll ans = 0;
	rep(i, n)
	{
		ll x, y, r;
		cin >> x >> y >> r;
		if (inverseX) {
			x = CONSTRAINT + 1 - x;
		}

		if (max(abs(x - s.second), abs(y - s.first)) <= r) {
			ans++;
		}
		else {
			imosx[max(y - r, 0LL)][max(x - r, 0LL)] += 1;
			imosx[max(y - r, 0LL)][min(x + r + 1, CONSTRAINT + 1)] += -1;
			imosy[max(x - r, 0LL)][max(y - r, 0LL)] += 1;
			imosy[max(x - r, 0LL)][min(y + r + 1, CONSTRAINT + 1)] += -1;
		}
	}

	vvll sumx(GSIZE, vll(GSIZE, 0)), sumy(GSIZE, vll(GSIZE, 0));
	rep(i, GSIZE) {
		ll sum = 0;
		rep(j, GSIZE)
		{
			sum += imosx[i][j];
			sumx[i][j] = sum;
		}
	}
	rep(i, GSIZE){
		ll sum = 0;
		rep(j, GSIZE) {
			sum += imosy[i][j];
			sumy[i][j] = sum;
		}
	}

	vector<vector<ll>> dist(GSIZE, vector<ll>(GSIZE, INF));
	// priority_queue<PPLL, vector<PPLL>, greater<PPLL>> q;
	// q.push({0, s});
	// dist[s.first][s.second] = 0;

	// while (!q.empty()) {
	// 	auto [nowCost, pos] = q.top();
	// 	auto [y, x] = pos;
	// 	q.pop();
	// 	if (dist[y][x] < nowCost) continue;

	// 	loop(i, 0, 1) {
	// 		ll nx = x + dx[i];
	// 		ll ny = y + dy[i];
	// 		if (nx < 1 || CONSTRAINT + 1 <= nx || ny < 1 || CONSTRAINT + 1 <= ny) continue;
	// 		// 下
	// 		if (i == 0) {
	// 			if (dist[ny][nx] <= nowCost + sumx[ny][nx]) continue;
	// 			dist[ny][nx] = nowCost + sumx[ny][nx];
	// 			q.push({dist[ny][nx], {ny, nx}});
	// 		}
	// 		else {
	// 			if (dist[ny][nx] <= nowCost + sumy[nx][ny]) continue;
	// 			dist[ny][nx] = nowCost + sumy[nx][ny];
	// 			q.push({dist[ny][nx], {ny, nx}});
	// 		}
	// 	}
	// }
	dist[s.first][s.second] = 0;
	loop(i, s.first, g.first)
	{
		loop(j, s.second, g.second) {
			chmin(dist[i + 1][j], dist[i][j] + sumx[i + 1][j]);
			chmin(dist[i][j + 1], dist[i][j] + sumy[j + 1][i]);
		}
	}

	cout << dist[g.first][g.second] + ans << endl;
	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) {}
	return 0;
}
