#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<n;i++)
#define loop(i,m,n) for(ll i=m;i<=n;i++)
//メイン
int main(){
	ll a,b;
	cin>>a>>b;
	if(a==b){
		cout<<-1<<endl;
		return 0;
	}
	loop (i,1,3){
		if(i!=a&&i!=b)cout<<i<<endl;
	}
	return 0;
}
