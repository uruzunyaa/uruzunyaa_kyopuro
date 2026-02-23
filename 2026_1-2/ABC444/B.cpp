//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	ll ans=0;

	for(ll i=1;i<=n;i++){
		string s =to_string(i);
		ll sm=0;
		rep(j,s.size()){
			sm+=s[j]-'0';
		}
		if(sm==k)ans++;
	}
	cout<<ans<<endl;
	return 0;
}
