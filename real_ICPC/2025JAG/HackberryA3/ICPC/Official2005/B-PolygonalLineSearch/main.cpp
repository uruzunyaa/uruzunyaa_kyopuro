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
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define rrep(i, n) for(ll i = n - 1; i >= 0; --i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
#define nC2(n) n * (n - 1) / 2
constexpr ll INF = 9009009009009009009LL;
constexpr int INF32 = 2002002002;
constexpr ll MOD = 998244353;
constexpr ll MOD107 = 1000000007;

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



template <typename T>
struct matrix {
private:
	vector<vector<T>> d;
	size_t n, m;
public:
	matrix(size_t n, size_t m, T init = T()) : d(n, vector<T>(m, init)), n(n), m(m) {}

	vector<T> operator[](size_t i) const { return d[i]; }
	vector<T>& operator[](size_t i) { return d[i]; }
	size_t rows() const { return n; }
	size_t cols() const { return m; }
	void resize(size_t new_n, size_t new_m, T init = T()) {
		d.resize(new_n);
		for (size_t i = 0; i < new_n; ++i) {
			d[i].resize(new_m, init);
		}
		n = new_n;
		m = new_m;
	}

	matrix& operator=(const matrix& other) { return *other; }
	matrix& operator+=(const matrix& other) {
		if (n != other.n || m != other.m) {
			throw std::invalid_argument("行列の足し算は同じサイズでなければなりません。" + std::to_string(n) + "x" + std::to_string(m) + " != " + std::to_string(other.n) + "x" + std::to_string(other.m));
		}
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] += other.d[i][j];
			}
		}
		return *this;
	}
	matrix& operator-=(const matrix& other) {
		if (n != other.n || m != other.m) {
			throw std::invalid_argument("行列の引き算は同じサイズでなければなりません。" + std::to_string(n) + "x" + std::to_string(m) + " != " + std::to_string(other.n) + "x" + std::to_string(other.m));
		}
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] -= other.d[i][j];
			}
		}
		return *this;
	}
	matrix& operator*=(const matrix& other) {
		if (m != other.n) {
			throw std::invalid_argument("行列の掛け算は、左側の列数と右側の行数が一致しなければなりません。" + std::to_string(m) + " != " + std::to_string(other.n));
		}
		matrix<T> result(n, other.m);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < other.m; ++j) {
				for (size_t k = 0; k < m; ++k) {
					result[i][j] += d[i][k] * other.d[k][j];
				}
			}
		}
		d = result.d;
		m = other.m;
		return *this;
	}
	matrix operator+(const matrix& other) const { return matrix(*this) += other; }
	matrix operator-(const matrix& other) const { return matrix(*this) -= other; }
	matrix operator*(const matrix& other) const { return matrix(*this) *= other; }

	bool operator==(const matrix& other) const {
		if (n != other.n || m != other.m) return false;
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				if (d[i][j] != other.d[i][j]) return false;
			}
		}
		return true;
	}
	bool operator!=(const matrix& other) const {
		return !(*this == other);
	}

	matrix& operator+=(const T& scalar) {
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] += scalar;
			}
		}
		return *this;
	}
	matrix& operator-=(const T& scalar) {
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] -= scalar;
			}
		}
		return *this;
	}
	matrix& operator*=(const T& scalar) {
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] *= scalar;
			}
		}
		return *this;
	}
	matrix& operator/=(const T& scalar) {
		if (scalar == 0) {
			throw std::invalid_argument("ゼロで割ることはできません。");
		}
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				d[i][j] /= scalar;
			}
		}
		return *this;
	}
	matrix operator+(const T& scalar) const { return matrix(*this) += scalar; }
	matrix operator-(const T& scalar) const { return matrix(*this) -= scalar; }
	matrix operator*(const T& scalar) const { return matrix(*this) *= scalar; }
	matrix operator/(const T& scalar) const { return matrix(*this) /= scalar; }

	matrix transpose() const {
		matrix<T> result(m, n);
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				result[j][i] = d[i][j];
			}
		}
		return result;
	}

	friend ostream& operator<<(ostream& os, const matrix<T>& mat) {
		for (size_t i = 0; i < mat.n; ++i) {
			for (size_t j = 0; j < mat.m; ++j) {
				os << mat.d[i][j];
				if (j != mat.m - 1) os << " ";
			}
			if (i != mat.n - 1) os << "\n";
		}
		return os;
	}
};

struct int2 {
	int64_t x, y;
	int2(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}

	double magnitude() {
		return sqrt(x * x + y * y);
	}
	int64_t sqr_magnitude() {
		return x * x + y * y;
	}
	int2 rotate90(int times = 1, int2 center = int2()) const {
		int64_t new_x = x - center.x;
		int64_t new_y = y - center.y;
		for (int i = 0; i < times; ++i) {
			int64_t temp = new_x;
			new_x = -new_y;
			new_y = temp;
		}
		return int2(new_x + center.x, new_y + center.y);
	}

	static int64_t dot(const int2& a, const int2& b) {
		return a.x * b.x + a.y * b.y;
	}
	static int64_t cross(const int2& a, const int2& b) {
		return a.x * b.y - a.y * b.x;
	}
	static double distance(const int2& a, const int2& b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}



	bool operator==(const int2& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const int2& other) const {
		return !(*this == other);
	}
	int2& operator=(const int2& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}
	int2 operator+(const int2& other) const {
		return int2(x + other.x, y + other.y);
	}
	int2 operator-(const int2& other) const {
		return int2(x - other.x, y - other.y);
	}
	int2 operator*(int64_t scalar) const {
		return int2(x * scalar, y * scalar);
	}
	int2 operator/(int64_t scalar) const {
		return int2(x / scalar, y / scalar);
	}
	int2& operator+=(const int2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	int2& operator-=(const int2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	int2& operator*=(int64_t scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	int2& operator/=(int64_t scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
};

struct double2 {
	double x, y;
	double2(double x = 0, double y = 0) : x(x), y(y) {}

	double magnitude() const {
		return sqrt(x * x + y * y);
	}
	double sqr_magnitude() const {
		return x * x + y * y;
	}
	double2 rotate(double rad, double2 center = double2()) const {
		double new_x = x - center.x;
		double new_y = y - center.y;
		double cos_angle = cos(rad);
		double sin_angle = sin(rad);
		double rotated_x = new_x * cos_angle - new_y * sin_angle;
		double rotated_y = new_x * sin_angle + new_y * cos_angle;
		return double2(rotated_x + center.x, rotated_y + center.y);
	}
	
	static double dot(const double2& a, const double2& b) {
		return a.x * b.x + a.y * b.y;
	}
	static double cross(const double2& a, const double2& b) {
		return a.x * b.y - a.y * b.x;
	}
	static double distance(const double2& a, const double2& b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}



	bool operator==(const double2& other) const {
		return x == other.x && y == other.y;
	}
	bool operator!=(const double2& other) const {
		return !(*this == other);
	}
	double2& operator=(const double2& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}
	double2 operator+(const double2& other) const {
		return double2(x + other.x, y + other.y);
	}
	double2 operator-(const double2& other) const {
		return double2(x - other.x, y - other.y);
	}
	double2 operator*(double scalar) const {
		return double2(x * scalar, y * scalar);
	}
	double2 operator/(double scalar) const {
		return double2(x / scalar, y / scalar);
	}
	double2& operator+=(const double2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	double2& operator-=(const double2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	double2& operator*=(double scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}
	double2& operator/=(double scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
};





int solve() {
	ll n; cin >> n;
	if (n == 0) return 1;
	vector<vector<int2>> graph(n + 1, vector<int2>());
	rep(i, n + 1) {
		ll m; cin >> m;
		graph[i].resize(m);
		rep(j, m) {
			ll x, y; cin >> x >> y;
			graph[i][j] = {x, y};
		}
	}

	auto ismatch = [&](vector<int2> a, vector<int2> b) -> bool {
		if (a.size() != b.size()) return false;
		int2 preva = a[0];
		int2 prevb = b[0];
		loop(i, 1, a.size() - 1) {
			int2 diffa = preva - a[i];
			int2 diffb = prevb - b[i];

			if (diffa != diffb) return false;

			preva = a[i];
			prevb = b[i];
		}
		return true;
	};

	vector<bool> matched(n + 1, false);
	rep(i, 4) {
		loop(j, 1, n) {
			if (ismatch(graph[0], graph[j])) matched[j] = true;
		}

		for (int2& p : graph[0]) {
			p = p.rotate90();
		}
	}
	loop(i, 1, n) {
		reverse(all(graph[i]));
	}
	rep(i, 4) {
		loop(j, 1, n) {
			if (ismatch(graph[0], graph[j])) matched[j] = true;
		}

		for (int2& p : graph[0]) {
			p = p.rotate90();
		}
	}

	loop(i, 1, n) {
		if(matched[i]) {
			cout << i << "\n";
		}
	}
	cout << "+++++" << "\n";

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	while (!solve()) { }

	return 0;
}
