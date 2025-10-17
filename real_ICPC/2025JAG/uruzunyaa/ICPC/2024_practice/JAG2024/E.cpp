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

	vl a(n+2,0);
	loop(i,1,n)cin>>a[i];

	//fが前からのDP、bが後ろからのDP
	vector<pair<ll,ll>> fdp(n+2,{0,m});
	vector<pair<ll,ll>> bdp(n+2,{0,m});

	//dp[i]=i番目の人まで案内した時、{何回目の発進か,搭乗後の搭乗人数};
	loop(i,1,n){
		if(fdp[i-1].second+a[i]>m){
			fdp[i]={fdp[i-1].first+1,a[i]};
		}else{
			fdp[i]={fdp[i-1].first,fdp[i-1].second+a[i]};
		}
	}
	ll ans=fdp[n].first;
	for(ll i=n;i>=1;i--){
		if(bdp[i+1].second+a[i]>m){
			bdp[i]={bdp[i+1].first+1,a[i]};
		}else{
			bdp[i]={bdp[i+1].first,bdp[i+1].second+a[i]};
		}
	}
	loop(i,1,n-1){
		ll tmp=0;
		//iとi+1が元々同じグループに属している場合は考慮しなくて良い
		tmp+=fdp[i-1].first;
		tmp+=bdp[i+2].first;
		if(fdp[i-1].second+a[i+1]>m)tmp++;
		if(bdp[i+2].second+a[i]>m)tmp++;
		ans=min(ans,tmp);
		
	}


	cout<<ans<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}