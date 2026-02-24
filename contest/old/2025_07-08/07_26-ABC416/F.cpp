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
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001


ll n,k;
vvl g;
vl a;

//最も遠い点を見つける。
ll st=0;
vl kyori;
void dfs(ll mae,ll node,ll cost){
	cost+=a[node];
	kyori[node]=cost;
	if(kyori[st]<kyori[node])st=node;
	rep(i,g[node].size()){
		if(g[node][i]==mae)continue;
		dfs(node,g[node][i],cost);
	}
	return;
}

vl dp(ll mae,ll node){
	vl ans={0};
	rep(i,g[node].size()){
		if(g[node][i]==mae)continue;
		vl tmp=dp(node,g[node][i]);
		rep(j,tmp.size()){
			ans.push_back(tmp[j]);
		}
	}
	sort(ans.rbegin(),ans.rend());
	while(ans.size()>k)ans.pop_back();
	ans[0]+=a[node];
	return ans;
}

//メイン
int main(){
	cin>>n>>k;
	rep(i,n){
		ll aa;
		cin>>aa;
		a.push_back(aa);
	}
	g=vvl(n);
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	kyori=vl(n,inf);
	dfs(-1,0,0);

	vl tmp = dp(-1,st);
	ll ans=0;
	rep(i,tmp.size()){
		ans+=tmp[i];
	}
	cout<<ans<<endl;

	return 0;
}
