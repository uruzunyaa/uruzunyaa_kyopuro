#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 1e9
#define mod 1000000007LL
#define eps 0.000000001


//メイン
int main(){
	ll n;
	cin>>n;
	vvl a(n,vl(n));
	rep(i,n)rep(j,n)cin>>a[i][j];

	vl dp(1LL<<n,0);
	dp[0]=1;

	rep(i,(1LL<<n)-1){
		rep(j,n){
			if(i&(1LL<<j))continue;
			if(a[__popcount(i)][j]==0)continue;
			dp[i+(1LL<<j)]+=dp[i];
			dp[i+(1LL<<j)]%=mod;
			
		}
	}

	cout<<dp[(1LL<<n)-1]<<endl;
	return 0;
}
