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
	vl one,two;
	rep(i,n){
		ll c,p;
		cin>>c>>p;
		if(c==1)one.push_back(p),two.push_back(0);
		else one.push_back(0),two.push_back(p);
	}
	Sums1d ones(one),twos(two);
	ll q;
	cin>>q;
	while(q--){
		ll l,r;
		cin>>l>>r;
		l--,r--;
		cout<<ones.get(l,r)<<" "<<twos.get(l,r)<<endl;
	}
	return 0;
}