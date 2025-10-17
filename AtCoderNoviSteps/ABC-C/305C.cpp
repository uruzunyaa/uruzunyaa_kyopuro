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
	ll h,w;
	cin>>h>>w;
	ll u=0,d=h-1,r=w-1,l=0;
	vector<string> s(h);
	rep(i,h)cin>>s[i];
	rep(i,h){
		ll cnt=0;
		rep(j,w){
			if(s[i][j]=='#')cnt++;
		}
		if(cnt==0)u=i+1;
		else break;
	}
	for(ll i=h-1;i>=0;i--){
		ll cnt=0;
		rep(j,w){
			if(s[i][j]=='#')cnt++;
		}
		if(cnt==0)d=i-1;
		else break;
	}

	rep(i,w){
		ll cnt=0;
		rep(j,h){
			if(s[j][i]=='#')cnt++;
		}
		if(cnt==0)l=i+1;
		else break;
	}
	for(ll i=w-1;i>=0;i--){
		ll cnt=0;
		rep(j,h){
			if(s[j][i]=='#')cnt++;
		}
		if(cnt==0)r=i-1;
		else break;
	}

	loop(i,u,d)loop(j,l,r){
		if(s[i][j]=='.')cout<<i+1<<" "<<j+1<<endl;
	}
	

	return 0;
}