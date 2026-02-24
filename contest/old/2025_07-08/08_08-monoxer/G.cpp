//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
#define eps 0.000000001

int main(){
ios::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
  
  int n;;
  cin >> n;
  vector<ll> a(n);
  rep(i,n)cin >> a[i];
  sort(a.begin(),a.end());
  vector<ll> big, small;
  rep(i,(n+1)/2){
    small.push_back(a[i]);
  }
  loop(i,(n+1)/2,n-1){
    big.push_back(a[i]);
  }

  vector<ll> b;
  while(!small.empty() || !big.empty()){
    if(!small.empty()){
      b.push_back(small.back());
      small.pop_back();
    }
    if(!big.empty()){
      b.push_back(big.back());
      big.pop_back();
    }
  }
  ll ans = 0;
  rep(i,n-1){
    ans += abs(b[i] - b[i+1]);
  }
  //奇数の時
  if(n&1){
    small.clear();
    big.clear();
    rep(i,n/2){
      small.push_back(a[i]);
    }
    loop(i,n/2,n-1){
      big.push_back(a[i]);
    }
    ll ans2 = 0;
    for(auto x:small) ans2 -= 2*x;
    ans2 += big[0];
    ans2 += big[1];
    loop(i,2,big.size()-1){
      ans2 += 2*big[i];
    }
    
    ans = max(ans, ans2);
  }
  
	return 0;
}