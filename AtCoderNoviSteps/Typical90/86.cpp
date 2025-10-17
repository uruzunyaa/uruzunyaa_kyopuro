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
#define mod 1000000007LL

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl x(q),y(q),z(q),w(q);
	rep(i,q)cin>>x[i]>>y[i]>>z[i]>>w[i],x[i]--,y[i]--,z[i]--;

	ll ans=1;
	rep(i,60){
		ll tmp=0;
		rep(b,1LL<<n){
			bool f=true;
			rep(j,q){
				ll calc=0;
				if(b&(1LL<<x[j]))calc=1;
				if(b&(1LL<<y[j]))calc=1;
				if(b&(1LL<<z[j]))calc=1;
				ll ws=0;
				if(w[j]&(1LL<<i))ws=1;
				if(ws^calc==1){
					f=false;
					break;
				}
			}
			if(f)tmp++;
		}
		ans*=tmp;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
