//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL


//メイン
int main(){
	ll n,w;
	cin>>n>>w;
	vvl g(4);
	vl c(n),v(n);
	rep(i,n){
		cin>>c[i]>>v[i];
		g[c[i]-c[0]].push_back(v[i]);
	}
	ll ans=0;
	rep(i,4)sort(g[i].rbegin(),g[i].rend());
	rep(i,min(w/c[0],(ll)g[0].size())){
		rep(j,min((w-i*c[0])/(c[0]+1),(ll)g[1].size())){
			rep(k,min((w-i*c[0]-j*(c[0]+1))/(c[0]+2),(ll)g[2].size())){
				rep(l,min((w-i*c[0]-j*(c[0]+1)-k*(c[0]+2))/(c[0]+3),(ll)g[3].size())){
					ll ans=max(ans,i*c[0]+j*(c[0]+1)+k*(c[0]+2)+l*(c[0]+3));
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
