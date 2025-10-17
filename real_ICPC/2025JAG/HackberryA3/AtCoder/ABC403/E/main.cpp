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




template <class T, typename T_Hash = hash<T>>
struct Trie {
private:
	struct Node {
		unordered_map<T, Node*, T_Hash> next;
		vector<int> accept;
		T c;
		int common;
		Node(T c) : c(c), common(0) {
		}
	};

	vector<Node*> nodes;
	Node* root;
	int n;

public:
	Trie() : root(new Node(-1)), n(0) {
		nodes.push_back(root);
	}

	/**
	 * @brief 文字列sをTrie木に挿入する O(|s|)
	 * @param s 挿入する文字列
	 * @param id 挿入する文字列のID(文字列の終端のノードにIDを保存しておく)
	 */
	template <class Iterable>
	void insert(const Iterable& s, int id) {
		Node* now = root;
		now->common++;
		for (const T& c : s) {
			if (!now->next.count(c)) {
				now->next[c] = new Node(c);
				nodes.push_back(now->next[c]);
			}
			now = now->next[c];
			now->common++;
		}
		now->accept.push_back(id);
		n++;
	}

	/**
	 * @brief 文字列sと完全一致する文字列がTrie木にいくつあるかを返す O(|s|)
	 */
	template <class Iterable>
	int count(const Iterable& s) {
		Node* now = root;
		for (const T& c : s) {
			if (!now->next.count(c)) return 0;
			now = now->next[c];
		}
		return now->accept.size();
	}

	size_t size() const {
		return n;
	}

	/**
	 * @brief 文字列sで始まる文字列がTrie木にいくつあるかを返す O(|s|)
	 */
	template <class Iterable>
	int start_with(const Iterable& s) {
		Node* now = root;
		for (const T& c : s) {
			if (!now->next.count(c)) return 0;
			now = now->next[c];
		}
		return now->common;
	}

	/**
	 * @brief 文字列sで始まる文字列を削除 O(|s|)
	 */
	template <class Iterable>
	void erase_start_with(const Iterable& s) {
		vector<Node*> history;

		Node* now = root;
		history.push_back(now);
		for (const T& c : s) {
			if (!now->next.count(c)) return;
			now = now->next[c];
			history.push_back(now);
		}

		int deletedCnt = 0;
		auto dfs = [&](auto self, Node* now) -> void {
			n -= now->accept.size();
			deletedCnt += now->accept.size();

			now->common = 0;
			now->accept.clear();

			for (auto& [c, next] : now->next) {
				self(self, next);
			}
		};
		dfs(dfs, now);

		while (history.size() > 0) {
			Node* now = history.back();
			now->common -= deletedCnt;
			history.pop_back();
		}
	}

	/**
	 * @brief 文字列sと共通する最長の接頭辞を返す O(|s|)
	 */
	template <class Iterable>
	vector<T> common_prefix(const Iterable& s) {
		vector<T> res;

		Node* now = root;
		for (const T& c : s) {
			if (!now->next.count(c)) return res;
			res.push_back(c);
			now = now->next[c];
		}
		return res;
	}

	/**
	 * @brief 文字列sと共通する接頭辞を持つ文字列の個数の最大値を返す O(|s|)
	 */
	template <class Iterable>
	int common_prefix_max(const Iterable& s) {
		Node* now = root;
		int mx = 0;
		for (const T& c : s) {
			if (!now->next.count(c)) return mx;
			now = now->next[c];
			mx = max(mx, now->common);
		}
		return mx;
	}

	/**
	 * @brief 文字列sと共通する接頭辞の合計の長さを返す O(|s|)
	 */
	template <class Iterable>
	int common_prefix_sum(const Iterable& s) {
		Node* now = root;
		int sum = 0;
		for (const T& c : s) {
			if (!now->next.count(c)) return sum;
			now = now->next[c];
			sum += now->common;
		}
		return sum;
	}

	/**
	* @brief 文字列sの接頭辞がTrie木にいくつあるかを返す O(|s|)
	*/
	template <class Iterable>
	int prefix_count(const Iterable& s) {
		Node* now = root;
		int cnt = 0;
		for (const T& c : s) {
			if (!now->next.count(c)) return cnt;
			now = now->next[c];
			cnt += now->accept.size();
		}
		return cnt;
	}
};

int solve() {
	ll q;
	cin >> q;

	Trie<char> x, y;
	rep(i, q) {
		ll t; cin >> t;
		string s; cin >> s;

		if (t == 1) {
			y.erase_start_with(s);
			x.insert(s, i);
		}
		else {
			if (!x.prefix_count(s)) {
				y.insert(s, i);
			}
		}

		cout << y.size() << endl;
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
