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

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//最上位bitの場所を求める
ll logs2(ll x){
  ll cnt=0;
	while(x!=0){
	  cnt++;
	  x/=2;
	}
	return cnt;
}


void solve(){
  ll n,k;
  cin>>n>>k;
  k--;
  if(power(2,logs2(n)-__popcount(n))<k+1){
    cout<<-1<<endl;
    return;
  }
  ll m=logs2(n);
  vl check;
  rep(i,m)if(!((1LL<<i)&n))check.push_back(i);
  rep(i,check.size()){
    if((1LL<<i)&k)n+=(1LL<<check[i]);
  }
  //vdbg(check);
  cout<<n<<endl;
  return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
