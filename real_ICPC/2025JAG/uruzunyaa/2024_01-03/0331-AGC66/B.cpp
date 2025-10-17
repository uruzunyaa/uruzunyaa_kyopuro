#include <bits/stdc++.h>
#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define rep(i,n) for(long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353

//メイン
int main(){
	vector<bbi> x(100);
	x[0]=1;
	rep(i,99)x[i+1]=x[i]*5;
	
	loop(i,50,99){
		cout<<x[i];
		rep(j,20)cout<<0;
	}
	cout<<endl;
	return 0;
}
