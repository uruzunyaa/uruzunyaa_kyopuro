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
#define mod 998244353
int main(){
	ll n,k;
	cin>>n>>k;

	vector<pair<ll,ll>>ab(n);

	rep(i,n)cin>>ab[i].first>>ab[i].second;

	sort(ab.rbegin(),ab.rend());

	loop(i,1,n-1)ab[i].second+=ab[i-1].second;

	rep(i,n){
		if(ab[i].second>k){
			cout<<ab[i].first+1<<endl;
			return 0;
		}
	}
	cout<<1<<endl;

	return 0;
}