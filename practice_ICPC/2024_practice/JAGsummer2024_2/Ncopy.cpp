#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n)for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n)for(ll i=m;i<=(ll)n;i++)
#define mod 998244353LL
#define vl vector<ll>
#define vvl vector<vector<ll>>


int main() {
	ll n;
	cin>>n;
	vvl e(1000001);
	loop(i,2,1000000){
		if(e[i].size()==0){
			for(ll j=i;j<=1000000;j+=i){
				e[j].push_back(i);
			}
		}
	}
	e[1].push_back(1);
	vector<pair<ll,ll>> dp(1000001,{0,1});
	dp[1].second=0;
	rep(i,n){
		ll a;
		cin>>a;
		vl pr=e[a];
		//debug
		// rep(j,pr.size())cout<<pr[j]<<" ";
		// cout<<endl;
		if(a==1){
			dp[1].first=1,dp[1].second++;
			continue;
		}
		pair<ll,ll> tmp={0,0};
		rep(b,1LL<<pr.size()){
			if(b==0)continue;
			ll mul=1;
			rep(j,pr.size())if(b&(1LL<<j))mul*=pr[j];
			if(tmp.first<=dp[mul].first){
				tmp.first=dp[mul].first+1;
				tmp.second=0;
				if(e[mul].size()%2==1)tmp.second+=dp[mul].second;
				else tmp.second-=dp[mul].second;
				tmp.second+=mod;
				tmp.second%=mod;
			}else if(tmp.first==dp[mul].first+1){
				if(e[mul].size()%2==1)tmp.second+=dp[mul].second;
				else tmp.second-=dp[mul].second;
				tmp.second+=mod;
				tmp.second%=mod;
			}
		}
		rep(b,1LL<<pr.size()){
			if(b==0)continue;
			ll mul=1;
			rep(j,pr.size())if(b&(1LL<<j))mul*=pr[j];
			dp[mul].first=tmp.first;
			dp[mul].second=tmp.second;
		}
	}
	ll L=1;
	ll ans=0;
	loop(i,1,1000000){
		if(dp[i].first>L){
			L=dp[i].first;
			ans=0;
			if(e[i].size()%2==1)ans+=dp[i].second;
			else ans-=dp[i].second;
			ans+=mod;
			ans%=mod;
		}else if(dp[i].first==L){
			if(e[i].size()%2==1)ans+=dp[i].second;
			else ans-=dp[i].second;
			ans+=mod;
			ans%=mod;
		}
	}
	cout<<L<<endl;
	cout<<ans<<endl;
}