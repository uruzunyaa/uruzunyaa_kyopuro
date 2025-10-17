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
  vector<P> a(n);
  rep(i, n) cin >> a[i].first >> a[i].second;

  map<P, ll> mp;
  rep(i, n) mp[a[i]] = i + 1;

  sort(a.rbegin(), a.rend());

  set<ll> cost;
  cost.insert(a[0].second);
  vll ans;
  ans.push_back(mp[a[0]]);
  loop(i, 1, n - 1) {
    if (cost.lower_bound(a[i].second)-- != cost.begin()) {
      cost.insert(a[i].second);
      continue;
    }
    cost.insert(a[i].second);
    ans.push_back(mp[a[i]]);
  }

  sort(ans.begin(), ans.end());

  cout << ans.size() << endl;
  for (auto x : ans)
    cout << x << " ";

  return 0;
}
