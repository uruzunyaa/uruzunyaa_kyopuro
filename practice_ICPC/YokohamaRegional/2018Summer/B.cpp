#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ll n; cin >> n;
    vector<pair<ll, string>> liquid(n);
    rep(i, n) cin >> liquid[i].second >> liquid[i].first;

    sort(liquid.begin(), liquid.end());

    ll m; cin >> m;
    ll last_density = 0;
    ll use = 0;
    rep(_, m) {
        string request; cin >> request;

        while (use < liquid.size() && (last_density >= liquid[use].first || request != liquid[use].second)) {
            use++;
        }
        if (use == liquid.size()) {
            cout << "No" << "\n";
            return 0;
        }

        last_density = liquid[use].first;
    }

    cout << "Yes" << "\n";
    return 0;
}