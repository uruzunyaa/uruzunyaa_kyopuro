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



struct Node {
	ll val;
	Node *left;
	Node *right;

	Node(ll val) : val(val) {
		left = nullptr;
		right = nullptr;
	}

	string tostr() const {
		string res = "";
		if (left != nullptr) {
			res += "(" + left->tostr() + ")";
		}
		else {
			res += "()";
		}

		res += "[" + to_string(val) + "]";

		if (right != nullptr) {
			res += "(" + right->tostr() + ")";
		}
		else {
			res += "()";
		}

		return res;
	}
};

int solve()
{
	string a, b;
	cin >> a >> b;

	auto parseTree = [](auto parseTree, string s, int &i) -> Node*
	{
		Node* left;
		ll val;
		Node* right;

		assert(s[i] == '(' || s[i] == ')');
		if (s[i] == ')')
		{
			return nullptr;
		}
		i++;
		left = parseTree(parseTree, s, i);
		assert(s[i] == ')');
		i++;

		assert(s[i] == '[');
		string valstr = "";
		while (s[++i] != ']')
		{
			valstr += s[i];
		}
		i++;
		val = stoi(valstr);

		assert(s[i] == '(');
		i++;
		right = parseTree(parseTree, s, i);
		assert(s[i] == ')');
		i++;

		Node* res = new Node(val);
		res->left = left;
		res->right = right;
		return res;
	};

	int i = 0;
	Node* treeA = parseTree(parseTree, a, i);
	i = 0;
	Node* treeB = parseTree(parseTree, b, i);

	auto merge = [](auto merge, Node* rootA, Node* rootB) -> Node* {
		Node* res = new Node(rootA->val + rootB->val);
		if (rootA->left != nullptr && rootB->left != nullptr) {
			res->left = merge(merge, rootA->left, rootB->left);
		}
		if (rootA->right != nullptr && rootB->right != nullptr) {
			res->right = merge(merge, rootA->right, rootB->right);
		}
		return res;
	};
	
	Node* ans = merge(merge, treeA, treeB);
	cout << ans->tostr() << endl;

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}

