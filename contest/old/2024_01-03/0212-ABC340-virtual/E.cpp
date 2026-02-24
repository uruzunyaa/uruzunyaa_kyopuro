#pragma GCC optimize("O3")
#include<bits/stdc++.h>
#include<atcoder/lazysegtree>
using namespace std;
using namespace atcoder;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

ll add(ll a,ll b){return a+b;}
ll addelement(){return 0;}
ll mx(ll a,ll b){return max(a,b);}
ll maxelement(){return -inf;}

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vl a(n);
	rep(i,n)cin>>a[i];

	lazy_segtree<ll,mx,maxelement,ll,add,add,addelement> lseg(a);
	rep(i,m){
		ll b;
		cin>>b;
		ll h=lseg.get(b);
		lseg.set(b,0);
		lseg.apply(0,n,h/n);
		h%=n;

		if(n>=h+b+1){
			lseg.apply(b+1,b+h+1,1);
		}else{
			lseg.apply(b+1,n,1);
			lseg.apply(0,h+b+1-n,1);
		}
	}
	rep(i,n){
		cout<<lseg.get(i)<<" ";
	}
	cout<<endl;
	return 0;
}
