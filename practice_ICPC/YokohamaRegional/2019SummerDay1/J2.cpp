#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)

vvl g;
vl x,y;
vector<bool> ck;

ll dfs(ll index){
	if(ck[index])return 0;
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

	ll ansmx=0;
	rep(i,m){
		ll tmp=dfs(i);
		if(tmp==0)continue;
		ansmx+=tmp-1;
	}

	///////////////////////////////////////////////////////////////////////////////
	vector<set<ll>> flowg(n * 2 + 2);
	ll G = n * 2 + 1;
	rep(i, m) {
		flowg[y[i]].insert(x[i] + n);
	}
	rep(i, n) {
		flowg[0].insert(i + 1);
		flowg[i + 1 + n].insert(G);
	}

	auto flowdfs = [&](auto dfs, ll v, vector<bool>& visited) -> bool {
		if (visited[v]) return false;
		if (v == G) return true;
		visited[v] = true;

		bool ok = false;
		ll okto = -1;
		for (ll to : flowg[v]) {
			if (dfs(dfs, to, visited)) {
				ok = true;
				okto = to;
				break;
			}
		}

		if (ok) {
			flowg[v].erase(okto);
			flowg[okto].insert(v);
		}
		
		return ok;
	};
	ll ansmn = 0;
	while (true) {
		vector<bool> visited(n * 2 + 2, false);
		if (flowdfs(flowdfs, 0, visited)) {
			ansmn++;
		}
		else {
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////////

	cout << m - ansmn << " " << ansmx << endl;
}