#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL
int main(){
	vl n(6);
	rep(i,6)cin>>n[i],n[i]%=mod;

	ll p=1,q=1;
	rep(i,3){
		p*=n[i];
		p%=mod;
		q*=n[i+3];
		q%=mod;
	}
	ll ans=p-q;
	if(ans<0)ans+=mod;

	cout<<ans<<endl;

	return 0;
}