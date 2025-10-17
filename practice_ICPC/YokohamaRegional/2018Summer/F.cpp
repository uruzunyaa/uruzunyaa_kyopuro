#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n;
	cin>>n;
	vl a(n);
	ll xr=0;
	rep(i,n){
		cin>>a[i];
		xr^=a[i];
	}

	if(xr==1){
		cout<<"Bob"<<endl;
		return 0;
	}
	if(xr!=0){
		cout<<"Alice"<<endl;
		return 0;
	}

	//xorが1に出来るか
	rep(i,n){
		xr^=a[i];
		if((xr^1)<a[i]){
			cout<<"Alice"<<endl;
			return 0;
		}
		xr^=a[i];
	}

	cout<<"Bob"<<endl;
	return 0;
}