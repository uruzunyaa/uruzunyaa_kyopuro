#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


//メイン
int main(){
	ll n,d,p;
	cin>>n>>d>>p;
	vl a(n);
	rep(i,n)cin>>a[i];

	vl sums={0};
	rep(i,n){
		sums.push_back(sums.back()+a[i]);
	}

	vvl dp(n+1,vl(n+1,0));
	rep(r,n+1)rep(l,r){
		if((sums[r]-sums[l])%d!=p)continue;
		dp[l][r]=(sums[r]-sums[l])/d;
	}

	rep(r,n+1)rep(l,r){
		loop(mid,l+1,r-1){
			dp[l][r]=max(dp[l][r],dp[l][mid]+dp[mid][r]);
		}
	}

	cout<<dp[0][n]<<endl;
	return 0;
}
