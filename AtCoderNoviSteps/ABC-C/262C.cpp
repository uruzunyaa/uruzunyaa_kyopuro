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
	vl a(n);
	rep(i,n)cin>>a[i],a[i]--;

	ll ans=0;
	ll tmp=0;
	rep(i,n){
		if(a[a[i]]==i&&a[i]>i)ans++;
		if(a[i]==i)tmp++;
	}
	ans+=tmp*(tmp-1)/2;
	cout<<ans<<endl;
	return 0;
}
