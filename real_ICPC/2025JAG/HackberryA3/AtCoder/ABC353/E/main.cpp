#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PP = pair<int, P>;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
#define all(v) v.begin(), v.end()
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
	for (int i = 0; i < v.size(); ++i) is >> v[i];
	return is;
}
template <typename T>
istream& operator>>(istream& is, vector<vector<T>>& vv) {
	assert(vv.size() > 0);
	for (int i = 0; i < vv.size(); ++i) is >> vv[i];
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




template <int char_size, int base>
struct Trie {
	struct Node {
		vector<Node*> next;
		vector<int> accept;
		int c;
		int common;
		Node(int c) : c(c), common(0) {
			next.assign(char_size, nullptr);
		}
	};

	vector<Node*> nodes;
	Node* root;
	Trie() : root(new Node(-1)) {
		nodes.push_back(root);
	}

	/**
	 * @brief 文字列sをTrie木に挿入する O(|s|)
	 * @param s 挿入する文字列
	 * @param id 挿入する文字列のID(文字列の終端のノードにIDを保存しておく)
	 */
	void insert(const string& s, int id) {
		Node* now = root;
		now->common++;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) {
				now->next[c] = new Node(c);
				nodes.push_back(now->next[c]);
			}
			now = now->next[c];
			now->common++;
		}
		now->accept.push_back(id);
	}

	/**
	 * @brief 文字列sと完全一致する文字列がTrie木にいくつあるかを返す O(|s|)
	 */
	int count(const string& s) {
		Node* now = root;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) return 0;
			now = now->next[c];
		}
		return now->accept.size();
	}

	/**
	 * @brief 文字列sで始まる文字列がTrie木にいくつあるかを返す O(|s|)
	 */
	int start_with(const string& s) {
		Node* now = root;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) return 0;
			now = now->next[c];
		}
		return now->common;
	}

	/**
	 * @brief 文字列sと共通する最長の接頭辞を返す O(|s|)
	 */
	string common_prefix(const string& s) {
		Node* now = root;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) return s.substr(0, i);
			now = now->next[c];
		}
		return s;
	}

	/**
	 * @brief 文字列sと共通する接頭辞を持つ文字列の個数の最大値を返す O(|s|)
	 */
	int common_prefix_max(const string& s) {
		Node* now = root;
		int mx = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) return mx;
			now = now->next[c];
			mx = max(mx, now->common);
		}
		return mx;
	}

	/**
	 * @brief 文字列sと共通する接頭辞の合計の長さを返す O(|s|)
	 */
	int common_prefix_sum(const string& s) {
		Node* now = root;
		int sum = 0;
		for (size_t i = 0; i < s.size(); ++i) {
			int c = s[i] - base;
			if (now->next[c] == nullptr) return sum;
			now = now->next[c];
			sum += now->common;
		}
		return sum;
	}
};

int solve() {
	ll n; cin >> n;
	Trie<26, 'a'> trie;

	ll ans = 0;
	rep(i, n) {
		string s; cin >> s;
		ans += trie.common_prefix_sum(s);
		trie.insert(s, i);
	}

	cout << ans << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
