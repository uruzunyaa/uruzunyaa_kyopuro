#include <bits/stdc++.h>
using namespace std;
#define FOR(i, m, n) for (int i = (m); i < (n); ++i)
#define REP(i, n) FOR(i, 0, n)
#define ALL(v) (v).begin(), (v).end()
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;
constexpr double EPS = 1e-8;
constexpr int MOD = 998244353;
// constexpr int MOD = 1000000007;
constexpr int DY4[]{1, 0, -1, 0}, DX4[]{0, -1, 0, 1};
constexpr int DY8[]{1, 1, 0, -1, -1, -1, 0, 1};
constexpr int DX8[]{0, -1, -1, -1, 0, 1, 1, 1};
template <typename T, typename U>
inline bool chmax(T &a, U b) { return a < b ? (a = b, true) : false; }
template <typename T, typename U>
inline bool chmin(T &a, U b) { return a > b ? (a = b, true) : false; }
struct IOSetup
{
	IOSetup()
	{
		std::cin.tie(nullptr);
		std::ios_base::sync_with_stdio(false);
		std::cout << fixed << setprecision(20);
	}
} iosetup;

#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)

// ICPC2019-Dから持ってくる
void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n);
	REP(i, n)cin >> a[i];
	REP(i,n/2){
		a[i]=a[i]+m-a[n-i-1];
		a[i]%=m;
	}
	while(a.size()>n/2)a.pop_back();
	a.insert(a.begin(),0);
	// a[i]がいくつ動かしたいか。

	a.erase(unique(a.begin(), a.end()), a.end());
	if (a.back() == m)a.pop_back();
	if (!a.empty() && a.front() == m)a.erase(a.begin());
	n = a.size();
	if (n == 0){
		cout<<0<<endl;
		return;
	}

	REP(i, n){
		if (a[i] == m)a[i] = 0;
	}

	ll ans = a.front();
	vector<pair<ll,ll>> dp(n,{0,0});
	loop(i,1,n-1){
		ll pl=a[i]-a[i-1]+m;
		ll mni=a[i-1]-a[i]+m;
		pl%=m,mni%=m;
		if()
		dp[i].first=min();
	}
	return;
}
