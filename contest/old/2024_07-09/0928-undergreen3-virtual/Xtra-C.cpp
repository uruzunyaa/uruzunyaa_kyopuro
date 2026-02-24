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
struct data{
	
};

pair<ll,ll> mdadd(pair<ll,ll> a,pair<ll,ll> b){return {(a.first+b.first)%26,(a.second+b.second)%26};}
pair<ll,ll> addelement(){return {0,0};}
ll gets(ll a,ll b){
	if()
}
ll getselement(){return 0;}

//メイン
int main(){
	string s,t;
	cin>>s>>t;
	ll n=max(s.size(),t.size());
	ll mn=min(s.size(),t.size());
	vector<pair<ll,ll>> a(n,{0,0});
	rep(i,mn)a[i]={s[i]-'a',(s[i]-t[i]+26)%26};
	lazy_segtree<pair<ll,ll>,mx,maxelement,pair<ll,ll>,mdadd,mdadd,addelement> lseg(a);
	
	ll q;
	cin>>q;
	rep(z,q){
		
	}
	return 0;
}
