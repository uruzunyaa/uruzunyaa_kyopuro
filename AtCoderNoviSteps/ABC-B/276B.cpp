#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll n,m;
	cin>>n>>m;
	vvl g(n+1);
	rep(i,m){
		ll a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	loop(i,1,n){
		sort(g[i].begin(),g[i].end());
		cout<<g[i].size();
		rep(j,g[i].size())cout<<" "<<g[i][j];
		cout<<endl;
	}
	return 0;
}