// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
ll solve(){
	ll n,m;
	cin>>n>>m;
	if(n==0)return 1;

	vl a(n+1),b(n+1);
	loop(i,1,n)cin>>a[i];
	loop(i,1,n){
		cin>>b[i];
		b[i]-=a[i];
		if(b[i]<0)b[i]+=m;
	}
	b[0]=0;
	vector<pair<ll,ll>> dp(n+1,{inf,inf});
	dp[0]={0,m};
	rep(i,n){
		if(b[i]<b[i+1]){
			dp[i+1].first=min(dp[i].second,dp[i].first+b[i+1]-b[i]);
			dp[i+1].second=dp[i].second+b[i+1]-b[i];
		}else if(b[i]>b[i+1]){
			dp[i+1].first=dp[i].first;
			dp[i+1].second=min(dp[i].first+b[i+1]+m-b[i],dp[i].second);
		}else {
			dp[i+1].first=dp[i].first;
			dp[i+1].second=dp[i].second;
		}
	}
	cout<<dp[n].first<<endl;
	rep(i,n+1)cout<<dp[i].first<<" ";
	cout<<endl;
	rep(i,n+1)cout<<dp[i].second<<" ";
	cout<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}