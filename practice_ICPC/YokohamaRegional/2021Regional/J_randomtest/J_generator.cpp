#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    const ll NMAX = 20;
    const ll XMAX = 500;
    const ll YMAX = 500;


    mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> rndN(2, NMAX);
    ll n = rndN(gen);

    unordered_set<ll> xleft, yleft;
    rep(i, XMAX) {
        xleft.insert(i + 1);
    }
    rep(i, YMAX) {
        yleft.insert(i + 1);
    }
    uniform_int_distribution<ll> rndX(1, XMAX);
    uniform_int_distribution<ll> rndY(1, YMAX);
    vector<ll> x(n), y(n);
    rep(i, n) {
        ll tmp = rndX(gen);
        while (!xleft.count(tmp)) {
            tmp = rndX(gen);
        }
        x[i] = tmp;
        xleft.erase(tmp);
    }
    rep(i, n) {
        ll tmp = rndY(gen);
        while (!yleft.count(tmp)) tmp = rndY(gen);
        y[i] = tmp;
        yleft.erase(tmp);
    }

    cout << n << "\n";
    rep(i, n) {
        cout << x[i] << " " << y[i] << "\n";
    }
    return 0;
}