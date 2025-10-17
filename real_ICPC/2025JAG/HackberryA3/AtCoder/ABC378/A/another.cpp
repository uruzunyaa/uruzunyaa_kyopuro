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
constexpr ll INF = 1001001001001001001LL;
constexpr int INF32 = 1001001001;
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




int f(ll a1, ll a2, ll a3, ll a4) {
	ll C = 0;
	if(a1==a2&&a3==a4){
        C=2;
    }else if(a1==a3&&a2==a4){
        C=2;
    }else if(a1==a2&&(a1!=a3||a1!=a4)){
        C=1;
    }else if(a1==a3&&(a1!=a2||a1!=a4)){
        C=1;
    }else if(a1==a4&&(a1!=a2||a1!=a3)){
        C=1;
    }else if(a2==a3&&(a2!=a1||a2!=a4)){
        C=1;
    }else if(a2==a4&&(a2!=a1||a2!=a3)){
        C=1;
    }else if(a3==a4&&(a3!=a1||a3!=a2)){
        C=1;
    }else{
        C=0;
    }

	return C;
}
int g() {
    int A[4];
    int a[4];
    
    int i, j;
    int c=0;
    
    for(i=0; i<4; i++){
        scanf("%d", &A[i]);
    }
    
    for(i=0; i<4; i++){
        a[i]=0;
    }
    
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            if(i+1==A[j]) a[i]++;
        }
    }
    
    for(i=0; i<4; i++){
        c=c+(a[i]/2);
    }
    
    printf("%d", c);
	return 0;
}
int answer(ll a1, ll a2, ll a3, ll a4) {
	vll a = {a1, a2, a3, a4};
	map<ll, ll> mp;
	ll ans = 0;
	rep(i, 4) {
		mp[a[i]]++;
		if (mp[a[i]] == 2)
		{
			ans++;
			mp[a[i]] = 0;
		}
	}
	
	return ans;
}

int solve() {
	rep(i, 4445) {
		ll j = i;
		ll a1 = j % 10;
		j /= 10;
		ll a2 = j % 10;
		j /= 10;
		ll a3 = j % 10;
		j /= 10;
		ll a4 = j % 10;
		j /= 10;

		if (1 <= a1 && a1 <= 4 && 1 <= a2 && a2 <= 4 && 1 <= a3 && a3 <= 4 && 1 <= a4 && a4 <= 4) {
			if (f(a1, a2, a3, a4) != answer(a1, a2, a3, a4)) {
				cout << a1 << a2 << a3 << a4 << endl;
				cout << f(a1, a2, a3, a4) << " " << answer(a1, a2, a3, a4) << endl;
				cout << endl;
			}
		}
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	return solve();
}
