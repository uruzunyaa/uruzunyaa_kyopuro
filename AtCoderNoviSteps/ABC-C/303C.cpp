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
	ll n,m,h,k;
	string s;
	cin>>n>>m>>h>>k>>s;
	set<pair<ll,ll>> xy;
	rep(i,m){
		ll x,y;
		cin>>x>>y;
		xy.insert(make_pair(x,y));
	}
	ll x=0,y=0;
	rep(i,n){
		if(h==0){
			cout<<"No"<<endl;
			return 0;
		}
		h--;
		if(s[i]=='R')x++;
		else if(s[i]=='L')x--;
		else if(s[i]=='U')y++;
		else y--;

		if(xy.count(make_pair(x,y))&&h<k){
			xy.erase(make_pair(x,y));
			h=k;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}