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
		sums=vl(n+1,0);
		rep(i,n){
			sums[i+1]=sums[i]+row[i];
		}
	}
	Sums1d(string row_s){
		n=(row_s.size());
		sums=vl(n+1,0);
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
	//末尾にXを追加する。
	void push_back(ll x){
		n++;
		sums.push_back(sums.back()+x);
	}
};

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	vl a(k,1);
	Sums1d sm(a);
	ll last=1;
	loop(i,k,n){
		ll tmp=sm.get(i-k,i-1);
		tmp%=1000000000;
		last=tmp;
		sm.push_back(tmp);
	}
	cout<<last<<endl;
	return 0;
}