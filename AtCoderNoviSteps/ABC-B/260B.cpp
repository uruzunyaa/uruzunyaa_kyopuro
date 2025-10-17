#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	ll n,x,y,z;
	cin>>n>>x>>y>>z;
	vl a(n);
	vl b(n);
	set<ll> ans;
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];

	vector<pair<ll,ll>> sx;
	rep(i,n)sx.push_back(make_pair(-a[i],i));
	sort(sx.begin(),sx.end());
	rep(i,x)ans.insert(sx[i].second);

	vector<pair<ll,ll>> sy;
	rep(i,n)if(!ans.count(i))sy.push_back(make_pair(-b[i],i));
	sort(sy.begin(),sy.end());
	rep(i,y)ans.insert(sy[i].second);

	vector<pair<ll,ll>> sz;
	rep(i,n)if(!ans.count(i))sz.push_back(make_pair(-a[i]-b[i],i));
	sort(sz.begin(),sz.end());
	rep(i,z)ans.insert(sz[i].second);

	for(const auto &val:ans){
		cout<<val+1<<endl;
	}
	return 0;
}