//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

// a/b < p/q < c/d を満たす、最小のqの内、最小のpを持つ物を求める。
pair<ll,ll> fracmiddle(ll a,ll b,ll c,ll d){
	//大きい方が無限大なら
	if(d==0)return {(a+1)/b,1};
	
	// a/bの整数部分とc/dの整数部分を比較
	if(a/b!=(c-1)/d)return {(a/b)+1,1};

	pair<ll,ll> tmp = fracmiddle(d,(c-1)%d+1,b,a%b);

	return {tmp.second+(a/b)*tmp.first,tmp.first};
}

void solve(){
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	ll ab=gcd(a,b);
	ll cd=gcd(c,d);
	a/=ab;
	b/=ab;
	c/=cd;
	d/=cd;

	//cout<<fracmiddle(a,b,c,d).first<<endl;
	cout<<fracmiddle(a,b,c,d).second<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
