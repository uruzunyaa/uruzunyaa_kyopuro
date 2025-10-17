#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n, a, b;
    cin >> n >> a >> b;

    set<ll> plans;
    rep(i, n) {
        ll d;
        cin >> d;
        ll mod = d % (a + b);
        plans.insert(mod);
    }

    vl days(plans.size());
    ll j = 0;
    for (auto it = plans.begin(); it != plans.end(); it++) {
        days[j] = *it;
        j++;
    }

    ll maxDiff = 0;
    rep(i, days.size() - 1) {
        maxDiff = max(maxDiff, days[i + 1] - days[i]);
    }
    // 週跨ぎ
    maxDiff = max(maxDiff, days[0] + (a + b - *days.rbegin()));

    cout << (b < maxDiff ? "Yes" : "No") << endl;
    return 0;
}
