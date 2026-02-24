#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, a, b; cin >> n >> a >> b;
    if (a != b) {
        cout << "NO" << endl;
        return 0;
    }

	if(a==0){
		cout<<"YES"<<endl;
		return 0;
	}
	ll m=n;

	n=n|(2*n);
	n=n&(2*n);
	n/=2;

	if(m==n){
		cout<<"YES"<<endl;
		return 0;
	}

	n=m;
	n=n&(2*n);
	n=n|(2*n);
	n/=2;
	if(m==n){
		cout<<"YES"<<endl;
		return 0;
	}
	cout<<"NO"<<endl;
	return 0;
}