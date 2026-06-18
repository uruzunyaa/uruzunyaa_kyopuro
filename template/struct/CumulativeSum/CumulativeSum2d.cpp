#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//二次元累積和を生成する。
struct CumulativeSum2d{
	ll h,w;
	vvl sums;
	CumulativeSum2d(vvl row){
		h=(row.size());
		w=(row[0].size());
		sums=vvl(h,vl(w,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row[i][j];
		}
	}
	CumulativeSum2d(vector<string> row_s){
		h=(row_s.size());
		w=(row_s[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row_s[i][j]-'0';
		}
	}
	//左上座標と右下座標を指定する。(半開区間でない)
	ll get(ll u,ll l,ll d,ll r){
		d++,r++;
		ll ans=0;
		ans+=sums[u][l];
		ans+=sums[d][r];
		ans-=sums[u][r];
		ans-=sums[d][l];
		return ans;
	}
};

//メイン
int main(){
	
}