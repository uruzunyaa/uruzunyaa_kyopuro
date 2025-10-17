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
vvl g(200001);
ll x,y;

bool dfs(ll b,ll t){
	bool tmp=false;
	if(t==x)tmp=true;

	rep(i,g[t].size()){
		if(g[t][i]==b)continue;
		if(dfs(t,g[t][i])){
			tmp= true;
		}
	}
	if(tmp){
		cout<<t<<" ";
		return true;
	}
	return false;
}
//メイン
int main(){
	ll n;
	cin>>n>>x>>y;

	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	dfs(-1,y);
	cout<<endl;

	return 0;
}
