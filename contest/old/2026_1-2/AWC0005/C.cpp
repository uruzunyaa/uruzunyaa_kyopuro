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
	ll n,k;
	cin>>n>>k;
	vl a(n);
	rep(i,n)cin>>a[i];
	
	//コピーを取っておく
	vl b=a;

	//左右から累積maxを流す
	rep(i,n-1)a[i+1]=max(a[i]-k,a[i+1]);
	rrep(i,n-1)a[i]=max(a[i+1]-k,a[i]);

	//変更前と比較し答えを求める
	ll ans=0;
	rep(i,n)ans+=a[i]-b[i];
	cout<<ans<<endl;
	return 0;
}
