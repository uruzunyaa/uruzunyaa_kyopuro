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


//メイン
int main(){
	//入力
	ll n,m;
	cin>>n>>m;
	string s,t;
	cin>>s>>t;

	//左から右にスタンプを消す
	rep(i,n-m+1){
		bool f=true;
		rep(j,m){
			if(s[i+j]!='#'&&s[i+j]!=t[j])f=false;
		}
		if(f){
			rep(j,m)s[i+j]='#';	
		}
	}

	//右から左にスタンプを消す
	rrep(i,n-m+1){
		bool f=true;
		rep(j,m){
			if(s[i+j]!='#'&&s[i+j]!=t[j])f=false;
		}
		if(f){
			rep(j,m)s[i+j]='#';	
		}
	}

	bool f=true;
	rep(i,n){
		if(s[i]!='#')f=false;
	}

	if(f)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
