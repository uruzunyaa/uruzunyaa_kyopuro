//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//ans[i]=Σa[j](jはiのsuperset)を求める。
//aの要素数は2の累乗でなくてはならない。
vl superset_sums(vl a){
	ll n=-inf;
	rep(i,30){
		ll asiz=a.size();
		if(asiz==(1LL<<i))n=i;
	}
	//下向きゼータ変換
	rep(i,n){
		rep(b,1LL<<n){
			if((b&(1LL<<i))==0)continue;
			a[b-(1LL<<i)]+=a[b];
		}
	}
	
	return a;
}
//注意：subset_sumsが動いたから大丈夫だろうの状態である。

int main(){
    
    return 0;
}