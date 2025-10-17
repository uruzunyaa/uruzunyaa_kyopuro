#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//メイン
int main(){
	//満たさない物を考えると、どれか一つ満たさない物を考えるから包除
	ll n,d;
	cin>>n>>d;
	vl a(n);
	rep(i,n)cin>>a[i];

	unsigned ll ans=1LL<<d;
	rep(i,1LL<<n){
		if(i==0)continue;
		ll tmp=0;
		rep(j,n){
			if(i&(1LL<<j)){
				tmp |= a[j];
			}
		}

		ll tmp2= 1LL<<(d-__popcount(tmp));

		if(__popcount(i)%2==1)ans -= tmp2;
		else ans += tmp2;
	}
	cout<<ans<<endl;
	return 0;
}
