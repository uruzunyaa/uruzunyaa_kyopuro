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
	ll n,m,p,q;
	cin>>n>>m>>p>>q;
	if(n==0)return 1;

	vl x(m);
	rep(i,m)cin>>x[i];
	
	ll pos=p;
	rep(i,m){
		if(pos==x[i])pos++;
		else if(pos-1==x[i])pos--;
	}
	if(pos==q){
		cout<<"OK"<<endl;
		return 0;
	}

	rep(j,m+1)loop(i,1,n-1){
		pos=p;
		vl y;
		rep(k,m){
			if(j==k)y.push_back(i);
			y.push_back(x[k]);
		}
		if(j==m)y.push_back(i);
		//cout<<y.size();
		rep(k,m+1){
			if(pos==y[k])pos++;
			else if(pos-1==y[k])pos--;
		}
		if(pos==q){
			cout<<i<<" "<<j<<endl;
			return 0;
		}
	}

	cout<<"NG"<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}