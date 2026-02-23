//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n){
		cin>>a[i];
	}

	sort(a.begin(),a.end());

	//{1,2,2,2,3}
	ll m=a[n/2];

	ll cnt=0;
	rep(i,n){
		if(a[i]==m)cnt++;
	}
	if(cnt>=(n+2)/2){
		cout<<"yes"<<endl;
		cout<<m<<endl;
	}else {
		cout<<"no"<<endl;
	}
	return 0;
}
