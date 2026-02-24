#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

ll n,q;
vector<bool> ans(901,false);
//メイン
void dfs(ll s,ll x,ll y,ll b){
	ans[s]=true;
	loop(i,2,x){
		loop(j,2,y){
			if(i*j>b)break;
			dfs(s-i*j,x-i,y-j,i*j);
		}
	}
	return;
}
int main(){
	cin>>n>>q;
	dfs(n*n,n,n,n*n);
	rep(i,q){
		ll k;
		cin>>k;
		if(ans[k])cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
