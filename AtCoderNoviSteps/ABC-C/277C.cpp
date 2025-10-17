#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
ll n;
map<ll,vl> g;
ll ans=1;
set<ll> check;

void dfs(ll d){
	if(check.count(d))return;
	check.insert(d);
	ans=max(ans,d);
	rep(i,g[d].size())dfs(g[d][i]);
	return;
}
//メイン
int main(){
	cin>>n;
	rep(i,n){
		ll aa,bb;
		cin>>aa>>bb;
		g[bb].push_back(aa);
		g[aa].push_back(bb);
	}
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
