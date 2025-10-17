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
	string s;
	cin>>n>>s;
	vl kodomo,otona;
	rep(i,n){
		ll a;
		cin>>a;
		if(s[i]=='0')kodomo.push_back(a);
		else otona.push_back(a);
	}
	sort(kodomo.begin(),kodomo.end());
	sort(otona.begin(),otona.end());
	ll ans=otona.size();
	rep(i,kodomo.size()){
		ll tmp=otona.end()-lower_bound(otona.begin(),otona.end(),kodomo[i]+1);
		ans=max(ans,i+tmp+1);
	}
	cout<<ans<<endl;
	return 0;
}
