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
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];

	vector<bool> c(360,false);
	c[0]=true;
	ll t=0;
	rep(i,n){
		t+=a[i];
		t%=360;
		c[t]=true;
	}
	ll ans=1;
	ll cnt=1;
	rep(i,720){
		if(c[i%360])cnt=1;
		else cnt++;
		ans=max(ans,cnt);
	}
	cout<<ans<<endl;
	return 0;
}