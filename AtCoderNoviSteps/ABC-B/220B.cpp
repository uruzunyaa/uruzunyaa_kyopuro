#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353

ll power(ll x,ll y){
	ll ans=1;
	rep(i,y){
		ans*=x;
	}
	return ans;
}
int main(){
	ll k;
	string a,b;
	cin>>k>>a>>b;

	ll x=0,y=0;

	rep(i,a.size()){
		x+=(a[a.size()-1-i]-'0')*pow(k,i);
	}

	rep(i,b.size()){
		y+=(b[b.size()-1-i]-'0')*pow(k,i);
	}

	cout<<x*y<<endl;

	return 0;
}