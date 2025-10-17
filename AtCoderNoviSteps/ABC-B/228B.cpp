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
	ll n,x;
	cin>>n>>x,x--;
	vl a(n);
	rep(i,n)cin>>a[i],a[i]--;
	vector<bool> c(n,true);
	ll ans=0;
	while(c[x]){
		c[x]=false;
		ans++;
		x=a[x];
	}
	cout<<ans<<endl;

	return 0;
}