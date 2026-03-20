//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vp vector<pair<ll,ll>>
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

//メイン
int main(){
	ll n;
	cin>>n;
	vl k(n),a(n);
	
	rep(i,n){
		cin>>k[i]>>a[i];
	}

	ll ans=-1;
	rep(ff,n)rep(ee,ff)rep(dd,ee)rep(cc,dd)rep(bb,cc)rep(aa,bb){
		set<ll> left,right;
		left.insert(k[aa]);
		left.insert(k[bb]);
		left.insert(k[cc]);
		left.insert(k[dd]);
		right.insert(k[cc]);
		right.insert(k[dd]);
		right.insert(k[ee]);
		right.insert(k[ff]);
		if(left.size()!=4||right.size()!=4)continue;
		ll tmp=a[aa]+a[bb]+a[cc]+a[dd]+a[ee]+a[ff];
		ans=max(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}
