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


//二次元累積和を生成する。
struct Sums2d{
	ll h,w;
	vvl sums;
	Sums2d(vvl row){
		h=(row.size());
		w=(row[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row[i][j];
		}
	}
	Sums2d(vector<string> row_s){
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
		if(d<u||r<l)return 0;
		d++,r++;
		ll ans=0;
		ans+=sums[u][l];
		ans+=sums[d][r];
		ans-=sums[u][r];
		ans-=sums[d][l];
		return ans;
	}
};

vector<string> gridTurn(vector<string> &s){
	ll h=s[0].size();
	ll w=s.size();
	vector<string> res(h,string(w,'.'));

	rep(i,h)rep(j,w){
		res[i][j]=s[w-j-1][i];
	}
	return res;
}

//メイン
int main(){
	ll h,w;
	cin>>h>>w;
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	if(h>w){
		swap(h,w);
		s=gridTurn(s);
	}
	rep(i,h)rep(j,w){
		if(s[i][j]=='#'){
			s[i][j]='0';
		}else{
			s[i][j]='1';
		}
	}
	Sums2d sums(s);
	ll ans=0;
	rep(d,h)rep(u,d+1){
		
		ll ups=-inf,downs=-inf;
		rep(r,w){

		}
	}

	return 0;
}
