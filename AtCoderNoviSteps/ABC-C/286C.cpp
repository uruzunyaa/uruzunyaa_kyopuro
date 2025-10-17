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
	ll n,a,b;
	string s;
	cin>>n>>a>>b>>s;
	ll ans=inf;
	ll suma=0;
	rep(i,n){
		ll sumb=0;
		rep(j,n/2)if(s[j]!=s[n-j-1])sumb+=b;
		ans=min(ans,suma+sumb);
		suma+=a;
		char tmp=*s.begin();
		s.erase(s.begin());
		s.push_back(tmp);
	}
	cout<<ans<<endl;
	return 0;
}