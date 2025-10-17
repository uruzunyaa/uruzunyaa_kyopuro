#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T> inline bool chmax(T &a, const T &b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

int main() {
  ll n;
  cin >> n;
  vector<string> s(n);
  vll rate(n);
  ll sumrate = 0;
  rep(i, n) {
    cin >> s[i] >> rate[i];
    sumrate += rate[i];
  }

  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - 1; ++j) {
      if (s[j] > s[j + 1]) {
        swap(s[j], s[j + 1]);
      }
    }
  }

  cout << s[sumrate % n] << endl;

  return 0;
}
