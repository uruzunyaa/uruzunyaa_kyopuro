#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)

int main() {
    ll n;
	cin>>n;
	if(n==1){
		cout<<"Yes"<<endl;
		cout<<1<<endl;
		return 0;
	}
	if(n%2==1){
		cout<<"No"<<endl;
		return 0;
	}

	vector<vector<ll>> ans(n,vector<ll>(n));

	rep(i,n){
		rep(j,(i+1)/2){
			ans[i][j]=i*2+1;
			ans[j][i]=i*2+2;
		}
	}
}