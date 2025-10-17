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
	string s;
	cin>>n>>s;

	set<pair<ll,ll>> m;
	m.insert({0,0});
	ll x=0,y=0;
	rep(i,n){
		if(s[i]=='R')x++;
		if(s[i]=='L')x--;
		if(s[i]=='U')y++;
		if(s[i]=='D')y--;
		if(m.count({x,y})){
			cout<<"Yes"<<endl;
			return 0;
		}
		m.insert({x,y});
	}
	cout<<"No"<<endl;
	return 0;
}