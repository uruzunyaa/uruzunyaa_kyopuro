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
	ll n,k;
	cin>>n>>k;
	vvl row(5001,vl(5001,0));
	if(k!=5000)k++;

	rep(i,n){
		ll a,b;
		cin>>a>>b;
		row[a][b]++;
	}

	vvl imos(5001,vl(5001,0));
	loop(i,1,5000)loop(j,1,5000){
		imos[i][j]=imos[i-1][j]+imos[i][j-1]-imos[i-1][j-1]+row[i][j];
	}

	ll ans=0;
	rep(i,5001-k)rep(j,5001-k){
		ll tmp=imos[i][j]+imos[i+k][j+k]-imos[i+k][j]-imos[i][j+k];
		ans=max(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}
