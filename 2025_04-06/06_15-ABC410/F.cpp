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
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001
//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int

//#include<atcoder/lazysegtree>


//グリッドを右に90度回転する。
vector<string> gridTurn(vector<string> &s){
	ll h=s[0].size();
	ll w=s.size();
	vector<string> res(h,string(w,'.'));

	rep(i,h)rep(j,w){
		res[i][j]=s[w-j-1][i];
	}

	return res;
}

void solve(){
	ll h,w;
	cin>>h>>w;
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	if(h>w)s=gridTurn(s),swap(h,w);

	vvl imos(h+1,vl(w+1,0));
	rep(i,h)rep(j,w){
		imos[i+1][j+1] = imos[i+1][j] + imos[i][j+1] - imos[i][j];
		if(s[i][j]=='#')imos[i+1][j+1]++;
		else imos[i+1][j+1]--;
	}

	long long ans=0;
	vl bk(h*w*2+1,0);
	bk[h*w]++;

	loop(j,1,h)loop(i,1,j){
		//i行目からj行目の矩形切り出しで答えを求める

		//ZeroSumRanges
		loop(k,1,w){
			ll now=imos[j][k]-imos[i-1][k]+h*w;
			ans+=bk[now];
			bk[now]++;
		}
		loop(k,1,w){
			ll now=imos[j][k]-imos[i-1][k]+h*w;
			bk[now]--;
		}

	}
	cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
