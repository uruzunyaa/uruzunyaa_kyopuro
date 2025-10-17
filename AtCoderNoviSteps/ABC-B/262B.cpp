#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	ll n,m;
	cin>>n>>m;
	vector<unordered_set<ll>> a(n);

	rep(i,m){
		ll u,v;
		cin>>u>>v,u--,v--;
		a[u].insert(v);
		a[v].insert(u);
	}
	ll ans=0;
	rep(i,n)rep(j,i)rep(k,j){
		if(a[i].count(j)&&a[i].count(k)&&a[j].count(k))ans++;
	}
	cout<<ans<<endl;
	return 0;
}