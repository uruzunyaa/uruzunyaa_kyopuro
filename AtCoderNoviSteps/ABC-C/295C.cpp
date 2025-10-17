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
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	sort(a.begin(),a.end());
	ll ans=0;
	rep(i,n-1){
		if(a[i]==a[i+1]){
			ans++;
			i++;
		}
	}
	cout<<ans<<endl;
	return 0;
}