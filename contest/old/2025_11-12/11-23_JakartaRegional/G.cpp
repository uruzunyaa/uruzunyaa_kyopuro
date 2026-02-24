#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define vl vector<ll>
#define vvl vector<vl>

bool dfs(vvl g){
	
}

int main() {
    ll n;
	cin>>n;
	vvl g(10,vl(10,0));
	rep(i,n){
		ll r,c;
		cin>>r>>c;
		g[r][c]=1;
	}

	if(dfs(g))cout<<"Kita"<<endl;
	else cout<<"Kami"<<endl;
    return 0;
}