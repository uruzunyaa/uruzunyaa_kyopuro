#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n;
	cin>>n;
	vl cnt(n,0);
	rep(i,n){
		ll a;
		cin>>a;
		ll m=a-i+n;
		m%=n;
		cnt[m]++;
	}
	ll ans=0;

	rep(i,n){
		ans=max(ans,cnt[i]+cnt[(i+1)%n]+cnt[(i+2)%n]);
	}
	cout<<ans<<endl;
	return 0;
}
