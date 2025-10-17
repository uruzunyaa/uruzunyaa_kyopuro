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
	ll n,w;
	cin>>n>>w;
	vl a(n);
	rep(i,n)cin>>a[i];
	a.push_back(0);
	a.push_back(0);
	n+=2;

	unordered_set<ll> b;
	rep(i,n)rep(j,i)rep(k,j){
		b.insert(a[i]+a[j]+a[k]);
	}
	ll ans=0;
	loop(i,1,w){
		if(b.count(i))ans++;
	}
	cout<<ans<<endl;
	return 0;
}