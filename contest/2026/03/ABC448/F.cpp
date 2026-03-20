//#pragma GCC optimize("O3")
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




//メイン
int main(){
	ll n;
	cin>>n;
	vvl xy(n,vl(3));
	rep(i,n){
		cin>>xy[i][0]>>xy[i][1];
		xy[i][2]=i+1;
	}
	ll blocksize=81649;

	sort(xy.begin(), xy.end(), [&](vl a, vl b) {
		int ablock = a[0] / blocksize, bblock = b[0] / blocksize;
		if(ablock != bblock) return ablock < bblock;
		return (ablock & 1) ? a[1] > b[1] : a[1] < b[1];
	});


	ll start=0;
	rep(i,n)if(xy[i][2]==1){
		start=i;
		break;
	}
	rep(i,n){
		cout<<xy[(start+i)%n][2]<<" ";
	}
	cout<<endl;
	return 0;
}
