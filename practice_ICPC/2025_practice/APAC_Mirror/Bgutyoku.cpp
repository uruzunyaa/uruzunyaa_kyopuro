#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000
vl ikeru(vvl g,ll node){
	vl ans;
	ans.push_back(node);
	for(auto val:g[node]){
		vl tmp=ikeru(g,val);
		rep(j,tmp.size()){
			ans.push_back(tmp[j]);
		}
	}
	return ans;
}

vvl eraseg(vvl g,ll node){
	vl tmp=ikeru(g,node);
	for(auto val:tmp){
		g[val].clear();
	}
	rep(i,g.size()){
		rep(j,g[i].size()){
			if(g[i][j]==node){
				g[i].erase(g[i].begin()+j);
			}
		}
	}
	return g;
}

ll cntg(vvl g,vl cost){
	ll ans=0;
	vl tmp=ikeru(g,0);
	for(auto val:tmp){
		if(cost[val]==-1)continue;
		ans++;
	}
	return ans;
}

ll game_dfs(vvl g,bool isfirst,vl cost){
	vl tmp=ikeru(g,0);
	if(cntg(g,cost)==1){
		for(auto val:tmp){
			if(cost[val]!=-1){
				return cost[val];
			}
		}
	}

	ll ans;
	if(isfirst)ans=inf;
	else ans=-inf;

	for(auto val:tmp){
		vvl eg=eraseg(g,val);
		if(cntg(eg,cost)==0)continue;
		ll nokoru=game_dfs(eg,!isfirst,cost);
		if(isfirst)ans=min(ans,nokoru);
		else ans=max(ans,nokoru);
	}

	return ans;
}

int main(){
    ll n;
	cin>>n;
	vvl g(n);
	loop(i,1,n-1){
		ll a;
		cin>>a;
		a--;
		g[a].push_back(i);
	}
	vl cost(n,-1);
	rep(i,n){
		if(g[i].size()==0)cost[i]=i+1;
	}

	// g=eraseg(g,1);
	// vl dbg=ikeru(g,0);
	// rep(i,dbg.size()){
	// 	cout<<dbg[i]<<" ";
	// }
	// cout<<endl;

	cout<<game_dfs(g,true,cost)<<endl;
}