#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < n; ++i)

int main(){
    ll n;
	cin>>n;
	vector<ll> a(n);
	rep(i,n)cin>>a[i];

	ll gcds=0;
	ll ans=0;
	rep(i,n-1){
		ans+=abs(a[i]-a[i+1]);
		gcds=gcd(gcds,abs(a[i]-a[i+1]));
	}
	gcds*=2;

	ll tmp=a[0];
	if(gcds!=0){
		tmp=a[0]%gcds;
	}
	if(tmp==0)tmp=gcds;
	cout<<tmp+ans<<endl;
}