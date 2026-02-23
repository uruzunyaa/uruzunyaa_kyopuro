//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#include<boost/multiprecision/cpp_int.hpp>
#define bbi boost::multiprecision::cpp_int
#define ll bbi
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
#define inf (1ULL<<63)


void solve(){
	ll n,m;
	cin>>n>>m;
	if(m==1){
		cout<<n<<endl;
		return;
	}
	if(n==1){
		cout<<1<<endl;
		return;
	}

	if(m<10){
		ll mn=2,mx=10000000000;

		while(mn!=mx){
			ll mid=mn+mx;
			mid/=2;
			ll ans=1;
			rloop(i,m+mid-1,mid)ans*=i;
			loop(i,1,m)ans/=i;
			if(ans>=n)mx=mid;
			else mn=mid+1;
		}
		cout<<mn<<endl;
		return ;
	}

	ll r=1;
	ll kotae=1;
	while(1){
		kotae*=m+r;
		kotae/=r;
		r++;
		if(kotae>=n){
			cout<<r<<endl;
			return;
		}
	}
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
