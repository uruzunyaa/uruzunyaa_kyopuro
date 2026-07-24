#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>

//1次元累積和を生成する。
struct Sums1d{
	ll n;
	vl sums;
	Sums1d(vl row){
		n=(row.size());
		sums=vl(n+1);
		rep(i,n){
			sums[i+1]=sums[i]+row[i];
		}
	}
	Sums1d(string row_s){
		n=(row_s.size());
		sums=vl(n+1);
		rep(i,n){
			sums[i+1]=sums[i]+row_s[i]-'0';
		}
	}
	//左と右を指定する。(半開区間でない)
	ll get(ll l,ll r){
		if(r<l)return 0;
		r++;
		ll ans=sums[r]-sums[l];
		return ans;
	}
};

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n-1);
	rep(i,n-1)cin>>a[i];
	Sums1d sm(a);
	ll q;
	cin>>q;
	ll ans=0;
	q--;
	ll now;
	cin>>now;
	while(q--){
		ll b;
		cin>>b;
		ans+=sm.get(min(now,b),max(now,b)-1);
		now=b;
	}
	cout<<ans<<endl;
	return 0;
}