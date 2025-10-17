#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL
int main(){
	ll n;
	cin>>n;
	ll ans=0;
	vl k(n);

	loop(i,1,n-1){
		ll ab=0;
		for(ll j=1;j*j<=i;j++){
			if(j*j==i)ab++;
			else if(i%j==0)ab+=2;
		}
		
		ll cd=0;
		for(ll j=1;j*j<=n-i;j++){
			if(j*j==n-i)cd++;
			else if((n-i)%j==0)cd+=2;
		}
		ans+=ab*cd;
	}
	cout<<ans<<endl;
	return 0;
}