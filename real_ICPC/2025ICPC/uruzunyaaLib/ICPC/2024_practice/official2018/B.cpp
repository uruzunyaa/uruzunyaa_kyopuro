// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#ifdef DEBUG
#include "cpp-dump/dump.hpp"
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#endif
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
ll solve(){
	ll w,h,t,p;
	cin>>w>>h>>t>>p;
	if(w==0)return 1;
	vector<vvl> k(t+1);

	k[0].assign(w,vl(h,1));
	rep(z,t){
		ll d,c;
		cin>>d>>c;
		if(d==1){
			ll x=max(w-c,c);
			k[z+1].assign(x,vl(h,0));
			rep(j,h){
				//左側
				rep(i,c){
					k[z+1][i][j]+=k[z][c-i-1][j];
				}
				//右側
				rep(i,w-c){
					k[z+1][i][j]+=k[z][c+i][j];
				}
			}
			w=x;
		}else{
			ll y=max(h-c,c);
			k[z+1].assign(w,vl(y,0));
			rep(i,w){
				//下側
				rep(j,c){
					k[z+1][i][j]+=k[z][i][c-j-1];
				}
				//上側
				rep(j,h-c){
					k[z+1][i][j]+=k[z][i][c+j];
				}
			}
			h=y;
		}
	}
	rep(i,p){
		ll x,y;
		cin>>x>>y;
		cout<<k[t][x][y]<<endl;
	}
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}