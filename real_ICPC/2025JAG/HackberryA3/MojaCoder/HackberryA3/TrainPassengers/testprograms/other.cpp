#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n, m; cin >> n >> m;
  ll sum = 0;
  ll maxCnt = m;
  for(ll i = 0; i < n; ++i) {
    ll a; cin >> a;
    if(a < 0) maxCnt += -a;
    else sum += a;
  }
  
  cout << (min(sum, maxCnt)) << endl;
}
