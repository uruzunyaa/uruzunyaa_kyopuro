#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード
mt19937_64 mt64(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


ll rndnxt(ll mn,ll mx){
	ll range=mx-mn+1;
	return mn+(((mt64()%range)+range)%range);
}

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


//メイン
int main(){
	ll n=2500,m=5000;
	cout<<n<<" "<<m<<endl;

	rep(i,n)cout<<rndnxt(1,1e9)<<" ";
	cout<<endl;

	rep(i,n){
		cout<<rndnxt(1,n)<<" "<<i+1<<endl;
	}
	rep(i,m-n){
		cout<<rndnxt(1,n)<<" "<<rndnxt(1,n)<<endl;
	}
	return 0;
}
