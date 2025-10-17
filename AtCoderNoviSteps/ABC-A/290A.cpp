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
	vl a(n);
	vl b(m);
	rep(i,n)cin>>a[i];
	rep(i,m)cin>>b[i],b[i]--;
	ll ans=0;
	rep(i,m){
		ans+=a[b[i]];
	}
	cout<<ans<<endl;
	return 0;
}