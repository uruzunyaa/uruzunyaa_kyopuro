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
	set<ll> odd,even;
	rep(i,n){
		ll a;
		cin>>a;
		if(a%2==0)odd.insert(a);
		else even.insert(a);
	}
	ll ans=-1;
	if(odd.size()>=2){
		auto it=odd.end();
		it--;
		ll tmp=*it;
		it--;
		tmp+=*it;
		ans=max(ans,tmp);
	}
	if(even.size()>=2){
		auto it=even.end();
		it--;
		ll tmp=*it;
		it--;
		tmp+=*it;
		ans=max(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}
