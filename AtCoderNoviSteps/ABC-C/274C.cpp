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
	vl ans={0};
	cout<<0<<endl;
	rep(i,n){
		ll a;
		cin>>a,a--;
		ans.push_back(ans[a]+1);
		ans.push_back(ans[a]+1);
		cout<<ans[a]+1<<endl;
		cout<<ans[a]+1<<endl;
	}
	return 0;
}