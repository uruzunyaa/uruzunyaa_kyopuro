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
	ll h,w;
	cin>>h>>w;
	vvl a(h,vl(w));
	vvl b=a;

	rep(i,h)rep(j,w)cin>>a[i][j];
	rep(i,h)rep(j,w)cin>>b[i][j];

	ll ans=0;

	rep(i,h-1)rep(j,w-1){
		ll tmp=b[i][j]-a[i][j];
		a[i][j]+=tmp;
		a[i][j+1]+=tmp;
		a[i+1][j]+=tmp;
		a[i+1][j+1]+=tmp;
		ans+=abs(tmp);
	}
	if(a==b)cout<<"Yes"<<endl<<ans<<endl;
	else cout<<"No"<<endl;
	return 0;
}
