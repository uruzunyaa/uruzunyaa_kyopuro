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
#define rep(i,n) for(long long i=0;i<n;i++)
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
	ll n;
	cin>>n;
	if(n==0)return 1;
	vl a(n);
	rep(i,n)cin>>a[i];
	vvl ans(n,vl(n,0));

	//端っこが一致してるとき
	if(a[n-1]==a[0]){
		rep(i,n){
			ans[0][n-i-1]=a[i];
			ans[n-1][i]=a[i];
			ans[i][0]=a[i];
			ans[n-i-1][n-1]=a[i];
		}
	}else{
		ll c;
		ll d;
		rep(i,n){
			if(a[0]==a[n-i-1]){
				c=n-i-1;
				break;
			}
		}
		rep(i,n){
			if(a[n-1]==a[i]){
				d=i;
				break;
			}
		}
		if(d>c){
			cout<<"No"<<endl;
			return 0;
		}
		//dとcの区間を埋める
		loop(i,d,c){
			ans[0][n-i-1]=a[i];
			ans[n-1][i]=a[i];
			ans[i][0]=a[i];
			ans[n-i-1][n-1]=a[i];
		}
		loop(i,1,n-2){
			ans[c][i]=a[i];
			ans[d][i]=a[n-i-1];
			ans[i][c]=a[n-i-1];
			ans[i][d]=a[i];
		}
	}
	cout<<"Yes"<<endl;
	rep(i,n){
		rep(j,n-1){
			cout<<ans[i][j]<<" ";
		}
		cout<<ans[i][n-1]<<endl;
	}
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}