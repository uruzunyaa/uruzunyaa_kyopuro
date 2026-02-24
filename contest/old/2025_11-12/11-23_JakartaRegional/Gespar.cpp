#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define vl vector<ll>
#define vvl vector<vl>



int main() {
    ll n;
	cin>>n;
	if(n%2==1){
		cout<<"Kita"<<endl;
		return 0;
	}
	ll gyakuten=0;
	rep(i,n){
		ll a,b;
		cin>>a>>b;
		if(a==1||b==1)continue;
		if((a+b)%2==0)gyakuten++;
	}
	if(gyakuten%2==0)cout<<"Kami"<<endl;
	else cout<<"Kita"<<endl;
}