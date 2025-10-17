#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vector<ll>>
int main(){
	ll h,w;
	cin>>h>>w;
	vvl p(h,vl(w));
	rep(i,h)rep(j,w)cin>>p[i][j];
	ll ans=0;
	//左上を全探索
	rep(i,h)rep(j,w){
		//伸ばす方向を積が10を超えないように全探索
		loop(k,1,10)loop(l,1,10/k){
			ll sum=0;
			if(i+k>h||j+l>w)continue;
			rep(a,k)rep(b,l){
				sum+=p[i+a][j+b];
			}
			if(sum==10){
				ans++;
				//cout<<i<<" "<<j<<endl;
				//out<<k<<" "<<l<<endl;
			}
		}
	}
	cout<<ans<<endl;
}