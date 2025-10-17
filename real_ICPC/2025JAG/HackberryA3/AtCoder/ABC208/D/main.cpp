#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1e15;

struct state
{
    ll sumDist;
    vll dists;
    ll from;

	state(ll sum, vll dists, ll from) : sumDist(sum), dists(dists), from(from) {}

    bool operator<(const state &rhs) { return this->sumDist < rhs.sumDist; }
    bool operator>(const state &rhs) { return this->sumDist > rhs.sumDist; }
};

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<PLL>> to(n, vector<PLL>());
    rep(i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        to[a].emplace_back(b, c);
    }

    ll ans = 0;
    rep(st, n) {
        vvll dists(n, vll(n, INF));
        priority_queue<state, vector<state>, greater<state>> q;
        q.emplace(dists[st] = vll(n, 0), st);

        while (!q.empty()) {
            ll from = q.top().from;
            vll curDists = q.top().dists;
            q.pop();

            bool isMinDist = true;
            rep(i, n) {
                if (dists[from][i] >= curDists[i]) {
                    isMinDist = false;
                    break;
                }
            }
            if (isMinDist) continue;

            for (auto v : to[from]) {
                ll to = v.first;
                ll cost = v.second;
                vll newDists = vll(n, INF);
                bool minDist = false;
                ll sumDist = 0;
                rep(i, n) {
                    if (to <= i) newDists[i] = dists[from][i] + cost;
                    if (newDists[i] < dists[to][i]) {
                        newDists[i] = min(newDists[i], dists[to][i]);
                        minDist = true;
                    }
                    sumDist += newDists[i];
                }
                dists[to] = newDists;
                if (minDist) { q.push(state(sumDist, newDists, to)); }
            }
        }

        rep(to, n) {
            rep(k, n) {
                if (dists[to][k] == INF) continue;
                ans += dists[to][k];
            }
        }
    }

    cout << ans << endl;

    return 0;
}
