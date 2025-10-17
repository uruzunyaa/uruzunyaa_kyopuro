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
mt19937_64 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

vector<vector<pair<ll,ll>>> t;
unordered_map<ll,ll> table;
vl cost;

void dfs(ll node,ll xr,ll before){
	cost[node]=xr;
	rep(i,t[node].size()){
		if(before==t[node][i].first)continue;
		dfs(t[node][i].first,xr^table[t[node][i].second],node);
	}
	return;
}
//メイン
int main(){
	ll n;
	cin>>n;
	t=vector<vector<pair<ll,ll>>>(n);
	cost=vl(n);
	rep(i,n-1){
		ll u,v,f;
		cin>>u>>v>>f;
		u--,v--;
		t[u].push_back({v,f});
		t[v].push_back({u,f});
		table[f]=mt();
	}
	dfs(0,0,0);
	ll q;
	cin>>q;
	while(q--){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		if(cost[a]==cost[b])cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
