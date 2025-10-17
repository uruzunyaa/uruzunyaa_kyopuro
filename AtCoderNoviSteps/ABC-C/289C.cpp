#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL
int main(){
	ll n,m;
	cin>>n>>m;
	vvl a(m);
	rep(i,m){
		ll c;
		cin>>c;
		rep(j,c){
			ll tmp;
			cin>>tmp;
			a[i].push_back(tmp);
		}
	}
	ll ans=0;
	rep(i,1LL<<m){
		unordered_set<ll> check;
		rep(j,m)if(i&(1LL<<j)){
			rep(k,a[j].size()){
				check.insert(a[j][k]);
			}
		}
		if(check.size()==n)ans++;
	}
	cout<<ans<<endl;
	return 0;
}