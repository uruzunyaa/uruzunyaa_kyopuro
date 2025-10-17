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
	ll tmp=51-(to_string(n).size());
	string ans;
	for(ll i=1000;i>100;i--){
		string s=to_string(n*i);
		rep(z,tmp)s.push_back('0');
		if(ans.find(s)==string::npos){
			ans+=s;
		}
	}
	return ans.size();
}
