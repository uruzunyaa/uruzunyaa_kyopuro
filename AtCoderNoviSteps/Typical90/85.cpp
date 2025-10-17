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
	ll k;
	cin>>k;

	vl y;
	for(ll i=1;i*i<=k;i++){
		if(k%i==0){
			y.push_back(i);
			if(i!=k/i)y.push_back(k/i);	
		}
	}

	sort(y.begin(),y.end());

	ll ans=0;
	rep(c,y.size()){
		rep(b,c+1){
			if(k/y[c]<y[b])break;
			if(k%(y[c]*y[b])!=0)continue;
			ll a=k/(y[c]*y[b]);
			if(a<=y[b])ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}
