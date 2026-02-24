//#pragma GCC optimize("O3")
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
#define Yes cout<<"Yes"<<endl;return 0;
#define No cout<<"No"<<endl;return 0;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL



//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n);
	vl w(n),a(n);
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	priority_queue<pair<ll,ll>> pq;
	
	rep(i,n)cin>>w[i],pq.push({-w[i],i});
	rep(i,n)cin>>a[i];
	vvl dp(n,vl(5000,1));

	ll ans=0;
	rep(z,n){
		ll tmp=pq.top().second;
		pq.pop();
		ans+=dp[tmp][w[tmp]-1]*a[tmp];
		rep(i,g[tmp].size()){
			for(ll j=w[g[tmp][i]]-w[tmp]-1;j>=0;j--){
				dp[g[tmp][i]][j+w[tmp]]=max(dp[g[tmp][i]][j+w[tmp]],dp[g[tmp][i]][j]+dp[tmp][w[tmp]-1]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
