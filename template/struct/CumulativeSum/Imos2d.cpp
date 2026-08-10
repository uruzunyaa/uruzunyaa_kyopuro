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

//2次元imos法。サイズ与えたら0初期化、配列ならそれで初期化。
//加算は閉矩形区間[{u,l},{d,r}]で行われる。
struct Imos2d{
	ll h,w;
	vvl sums;
	Imos2d(ll height,ll width){
		h=height;
		w=width;
		sums=vvl(h+1,(vl(w+1,0)));
	}
	Imos2d(vvl a){
		h=a.size();
		w=a[0].size();
		sums=vvl(h+1,(vl(w+1,0)));
		rep(i,h)rep(j,w){
			sums[i][j]+=a[i][j];
			sums[i+1][j+1]+=a[i][j];
			sums[i][j+1]-=a[i][j];
			sums[i+1][j]-=a[i][j];
		}
	}
	//[l,r]にxを加算
	void add(ll u,ll l,ll d,ll r,ll x){
		if(d<u)return;
		if(r<l)return;
		d++;
		r++;
		
		sums[u][l]+=x;
		sums[d][r]+=x;
		sums[u][r]-=x;
		sums[d][l]-=x;
	}
	//現時点を復元して返す。
	vvl get(){
		vvl ans(h,vl(w));
		rep(i,h)rep(j,w){
			ans[i][j]=sums[i][j];
			if(i!=0)ans[i][j]+=ans[i-1][j];
			if(j!=0)ans[i][j]+=ans[i][j-1];
			if(i!=0&&j!=0)ans[i][j]-=ans[i-1][j-1];
		}
		return ans;
	}
};
//メイン
int main(){

	return 0;
}
