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

// nのk乗をmodで割った余りを計算(modはdefineで定義想定)
ll powerMod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%MOD;
		n=n*n%MOD;
		k >>= 1;
	}
	return result;
}

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




string next(char c, string& s, int& i) {
	string res;
	while (s[i] != c) {
		res += s[i];
		i++;
	}
	return res;
}

int solve() {
	string e; cin >> e;

	set<string> m;
	auto dfs = [&](auto dfs, int& i) -> void {
		if ('0' <= e[i] && e[i] <= '9') {
			i++;
			return;
		}

		assert(e[i] == 'i' && e[i + 1] == 'f' && e[i + 2] == '_');
		i += 3;

		string var = next('_', e, i);
		m.insert(var);
		i++;

		assert(e[i] == 't' && e[i + 1] == 'h' && e[i + 2] == 'e' && e[i + 3] == 'n' && e[i + 4] == '_');
		i += 5;

		dfs(dfs, i);
		i++;

		assert(e[i] == 'e' && e[i + 1] == 'l' && e[i + 2] == 's' && e[i + 3] == 'e' && e[i + 4] == '_');
		i += 5;

		dfs(dfs, i);
	};
	int i = 0;
	dfs(dfs, i);

	//cout << m.size() << endl;
	map<string,pair<bool,ll>> mp;
	ll ans=0;
	auto dfs2 = [&](auto dfs2, int& i ,bool flag) -> void {
		if ('0' <= e[i] && e[i] <= '9') {
			//TODO 何回足されるかを計算
			if(flag){
				ans+=powerMod(2,(m.size()-mp.size()))*(e[i]-'0');
				ans%=MOD;
			}
			i++;
			return;
		}

		assert(e[i] == 'i' && e[i + 1] == 'f' && e[i + 2] == '_');
		i += 3;

		//変数名の取得
		string var = next('_', e, i);
		m.insert(var);
		i++;

		assert(e[i] == 't' && e[i + 1] == 'h' && e[i + 2] == 'e' && e[i + 3] == 'n' && e[i + 4] == '_');
		i += 5;

		//TODO true条件を付ける
		if(mp.count(var)){
			mp[var].second++;
			if(mp[var].first){
				dfs2(dfs2, i , flag);
			}else{
				dfs2(dfs2, i , false);
			}
			mp[var].second--;
		}else{
			mp[var]={true,1};
			dfs2(dfs2, i , flag);
			mp.erase(var);
		}

		
		i++;
		
		//TODO true条件を消す

		
		assert(e[i] == 'e' && e[i + 1] == 'l' && e[i + 2] == 's' && e[i + 3] == 'e' && e[i + 4] == '_');
		i += 5;

		//TODO else条件を付ける
		if(mp.count(var)){
			mp[var].second++;
			if(!mp[var].first){
				dfs2(dfs2, i , flag);
			}else{
				dfs2(dfs2, i , false);
			}
			mp[var].second--;
		}else{
			mp[var]={false,1};
			dfs2(dfs2, i , flag);
			mp.erase(var);
		}
		//TODO else条件を付ける
	};
	i = 0;
	dfs2(dfs2, i ,true);
	
	cout<<ans<<"\n";
	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
