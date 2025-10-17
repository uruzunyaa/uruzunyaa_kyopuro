#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll n;
	cin>>n;
	vl x(n),y(n),h(n);
	ll xx,yy,hh;
	rep(i,n){		
		cin>>x[i]>>y[i]>>h[i];
		if(h[i]!=0)xx=x[i],yy=y[i],hh=h[i];
	}
	rep(i,101){
		rep(j,101){
			ll ansh=hh+abs(i-xx)+abs(j-yy);
			bool f=true;
			rep(k,n){
				if(max(0LL,ansh-abs(i-x[k])-abs(j-y[k]))!=h[k])f=false;
			}
			if(f)cout<<i<<" "<<j<<" "<<ansh<<endl;
		}
	}
	return 0;
}
