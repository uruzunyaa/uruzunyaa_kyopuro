#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

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



map<pair<ll,ll>,ll> cash;

//場合の数 nCr を求める
ll ncr(ll n,ll r) {
	if(n<r)return 0;
	if(cash.count({n,r}))return cash[{n,r}];
	vvl dp(n+1,vl(r+1));
	rep (i,n+1)dp[i][0] = 1;
	rep (i,r+1)dp[i][i] = 1;
	loop (i,1,n){
		loop (j,1,min((ll)i-1,r)) {
			//nCr= n-1Cr-1 + n-1Cr
			dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
		}
	}
	cash[{n,r}]=dp[n][r];
	return dp[n][r];
}

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	vl a(n);
	rep(i,n)cin>>a[i];
	vvl dp(n+1,vl(k+1,0));

	rep(i,n)dp[i][0]=1;
	rep(i,n){
		loop(j,0,k){
			loop(h,0,k-j){
				//j個選んでる状態から、h個新たに選ぶ
				dp[i+1][j+h]+=((dp[i][j]*ncr(k-j,h))%mod)*power_mod(a[i],h);
				dp[i+1][j+h]%=mod;
			}
		}
	}
	ll ans=0;
	rep(i,n){
		ans+=dp[i+1][k];
		ans%=mod;
	}
	//vvdbg(dp);
	cout<<ans<<endl;
	return 0;
}
