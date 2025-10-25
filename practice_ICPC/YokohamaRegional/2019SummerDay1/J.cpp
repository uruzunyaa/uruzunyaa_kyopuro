#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)

vvl g;
vl x,y;
set<ll> tate,yoko;
vector<bool> ck;

ll dfs(ll index){
	if(ck[index])return 0;
	tate.insert(x[index]);
	yoko.insert(y[index]);
	ck[index]=true;
	ll ans=1;
	rep(i,g[index].size()){
		ans+=dfs(g[index][i]);
	}
	return ans;
}

int main(){
    ll n,m;
	cin>>n>>m;
	g=vvl(m);
	x=vl(m);
	y=vl(m);
	ck=vector<bool>(m,false);
	rep(i,m){
		cin>>x[i]>>y[i];
	}

	rep(i,m)rep(j,i){
		if(x[i]==x[j]||y[i]==y[j]){
			g[i].push_back(j);
			g[j].push_back(i);
			//cout<<i<<" "<<j<<endl;
		}
	}

	ll ansmn=0,ansmx=0;
	rep(i,m){
		ll tmp=dfs(i);
		if(tmp==0)continue;
		ansmx+=tmp-1;
		ansmn+=tmp-min(tate.size(),yoko.size());
		cout<<i<<" "<<min(tate.size(),yoko.size())<<endl;
		tate.clear();
		yoko.clear();
	}
	cout<<ansmn<<" "<<ansmx<<endl;
}