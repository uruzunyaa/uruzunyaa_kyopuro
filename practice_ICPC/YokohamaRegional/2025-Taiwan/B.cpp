#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, l, x, y; cin >> n >> m >> l >> x >> y;
    vector<PLL> buses;
    vector<double> bustimes(n);
    rep(i, n) {
        ll s, t; cin >> s >> t;
        buses.push_back({s, i});
        buses.push_back({t, i});
        double time = (t - s) / (double)x;
        time += (l - t) / (double)y;
        bustimes[i] = time;
    }

    vector<PLL> people(m);
    rep(i, m) {
        ll p; cin >> p;
        people[i] = {p, i};
    }

    sort(buses.rbegin(), buses.rend());
    sort(people.begin(), people.end());

    vector<double> ans(m);
    unordered_set<ll> nowbus;
    map<double, ll> time;
    rep(i, m) {
        ll p = people[i].first;

        while (!buses.empty() && buses.back().first <= p) {
            auto [s, busi] = buses.back();
            buses.pop_back();
            if (nowbus.count(busi)) {
                nowbus.erase(busi);
                time[bustimes[busi]]--;
                if (time[bustimes[busi]] == 0) time.erase(bustimes[busi]);
            }
            else {
                nowbus.insert(busi);
                time[bustimes[busi]]++;
            }
        }

        double walk = (l - p) / (double)y;
        double riding = nowbus.size() != 0 ? time.begin()->first : INF;
        ans[people[i].second] = min(walk, riding);
    }

    rep(i, m) {
        cout << fixed << setprecision(13) << ans[i] << '\n';
    }
}