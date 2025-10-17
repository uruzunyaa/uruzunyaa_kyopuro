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




struct Date {
	ll weekday;
	ll hour;
	ll minute;

	Date(ll weekday, ll hour, ll minute) : weekday(weekday), hour(hour), minute(minute) {}

	Date add(ll minute) const {
		Date res(this->weekday, this->hour, this->minute);
		res.minute += minute;

		res.hour += res.minute / 60;
		res.minute %= 60;

		res.weekday += res.hour / 24;
		res.hour %= 24;

		res.weekday %= 7;
		return res;
	}
};

bool isAllNight(Date s, Date g) {
	if (s.hour <= g.hour) {
		return (18 <= s.hour && s.hour < 24 && 18 <= g.hour && g.hour < 24) || (0 <= s.hour && s.hour < 6 && 0 <= g.hour && g.hour < 6);
	}
	else {
		return (18 <= s.hour && s.hour < 24 && 0 <= g.hour && g.hour < 6);
	}
}
bool isAllDay(Date s, Date g) {
	if (s.hour <= g.hour) {
		return (6 <= s.hour && s.hour < 18 && 6 <= g.hour && g.hour < 18);
	}
	return false;
}

unordered_map<string, ll> wd_map = {
	// Sun, Mon, Tue, Wed, Thu, Fri, Sat
	{"Sun", 0},
	{"Mon", 1},
	{"Tue", 2},
	{"Wed", 3},
	{"Thu", 4},
	{"Fri", 5},
	{"Sat", 6}};

int solve()
{
	ll s; cin >> s;
	if (s == 0)
		return 1;
	ll n, t;
	cin >> n >> t;
	string weekday, time;
	cin >> weekday >> time;
	ll p, m;
	cin >> p >> m;

	double ans = -INF32;
	rep(hour, 24) rep(minute, 60) rep(wd, 7)
	{
		ll ok = 0;
		Date now(wd, hour, minute);

		for (ll stage = 0; stage < m; stage++, now = now.add(t)) {
			Date start = now;
			Date end = start.add(s);

			if (weekday != "All" && (start.weekday != wd_map[weekday] || end.weekday != wd_map[weekday])) {
				continue;
			}
			if (time == "Day" && !isAllDay(start, end)) {
				continue;
			}
			else if (time == "Night" && !isAllNight(start, end)) {
				continue;
			}

			ok += n;
		}

		chmax(ans, 1 - pow(1.0 - (1.0 / p), ok));
	}

	cout << fixed << setprecision(10) << ans << endl;
	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) {}
	return 0;
}
