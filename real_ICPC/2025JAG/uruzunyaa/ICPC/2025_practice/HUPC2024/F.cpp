//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define YES cout<<"Yes"<<endl;return 0;
#define NO cout<<"No"<<endl;return 0;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int

//#include<atcoder/lazysegtree>

//√の値が整数かを調べる
bool isSqrt(ll n) {
	if (n < 0) return false;
	ll sqrtN = static_cast<ll>(sqrt(n));
	return sqrtN * sqrtN == n;
}

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//素因数分解
vector<ll> makePrime(ll n){
	vector<ll> factors;
	while (n % 2 == 0) {
		factors.push_back(2);
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors.push_back(i);
			n /= i;
		}
	}
	if (n > 2) {
		factors.push_back(n);
	}
	return factors;
}

//map形式で、nを素因数分解した値を返す
map<ll,ll> makeMapPrime(ll n){
	map<ll,ll> factors;
	while (n % 2 == 0) {
		factors[2]++;
		n /= 2;
	}
	for (ll i=3; i*i<=n;i+=2) {
		while (n%i == 0) {
			factors[i]++;
			n /= i;
		}
	}
	if (n > 2) {
		factors[n]++;
	}
	return factors;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}

//mod mにおけるaの逆元を計算
ll modinv(ll a, ll m) {
	ll b = m, u = 1, v = 0;
	while (b) {
		ll t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m; 
	if (u < 0) u += m;
	return u;
}

//場合の数 nCr を求める
ll ncr(ll n,ll r) {
	if(n<r)return 0;
	vvl dp(n+1,vl(r+1));
	rep (i,n+1)dp[i][0] = 1;
	rep (i,r+1)dp[i][i] = 1;
	loop (i,1,n){
		loop (j,1,min((ll)i-1,r)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
		}
	}
	return dp[n][r];
}



//メイン
int main(){
	vvl ncr(100001,vl(10));
	rep (i,100001)ncr[i][0] = 1;
	rep (i,10)ncr[i][i] = 1;
	loop (i,1,100000){
		loop (j,1,min((ll)i-1,9LL)) {
			//nCr= n-1Cr-1 + n-1Cr
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
			ncr[i][j] %= mod;
		}
	}

	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];

	vector<vector<vvl>> dp(n+1,vector<vvl>(10,vvl(3,vl(3,0))));
	dp[0][0][0][0]=1;
	
	rep(i,n)rep(j,10)rep(k,3)rep(l,3){
		rep(e,min(10-j,a[i]+1)){
			//dp[i][j][k][l]から新たにe個選ぶ
			ll tmp=e;
			tmp-=k;
			tmp-=l;
			if(tmp<0)continue;

			dp[i+1][j+e][tmp%3][k]+=dp[i][j][k][l]*ncr[a[i]][e];
			dp[i+1][j+e][tmp%3][k]%=mod;
		}
	}
	cout<<dp[n][9][0][0]<<endl;
	return 0;
}
