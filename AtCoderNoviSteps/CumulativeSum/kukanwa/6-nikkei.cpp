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

//1次元累積和を生成する。
struct Sums1d{
	ll n;
	vl sums;
	Sums1d(vl row){
		n=(row.size());
		sums=vl(n+1);
		rep(i,n){
			sums[i+1]=sums[i]+row[i];
		}
	}
	Sums1d(string row_s){
		n=(row_s.size());
		sums=vl(n+1);
		rep(i,n){
			sums[i+1]=sums[i]+row_s[i]-'0';
		}
	}
	//左と右を指定する。(半開区間でない)
	ll get(ll l,ll r){
		if(r<l)return 0;
		r++;
		ll ans=sums[r]-sums[l];
		return ans;
	}
};

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	vl ans(n,0);
	rep(i,n)cin>>a[i];
	Sums1d sm(a);
	rep(r,n)rep(l,r+1){
		ans[r-l]=max(ans[r-l],sm.get(l,r));
	}
	vdbg(ans);
	return 0;
}