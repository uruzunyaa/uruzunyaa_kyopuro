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
	ll n,q;
	cin>>n>>q;
	vvl a(n);
	rep(i,n){
		ll l;
		cin>>l;
		ll aa;
		rep(j,l)cin>>aa,a[i].push_back(aa);
	}

	rep(i,q){
		ll s,t;
		cin>>s>>t,s--,t--;
		cout<<a[s][t]<<endl;
	}
	return 0;
}