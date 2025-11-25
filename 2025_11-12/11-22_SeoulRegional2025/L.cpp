#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<n;i++)
#define inf 1000000000000000000LL
int main(){
	ll n,q;
	cin>>n>>q;
	ll lmax=0,rmin=inf;
	rep(i,n){
		ll l,r,y;
		cin>>l>>r>>y;
		lmax=max(l,lmax);
		rmin=min(r,rmin);
	}

	while(q--){
		ll x;
		cin>>x;
		ll ans=max(x-rmin,lmax-x);
		ans=max(ans,0LL);
		cout<<ans<<endl;
	}
	
}