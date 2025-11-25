#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main(){
    ll n, r;
    cin >> n >> r;
    vector<ll> x(n), y(n), z(n);
    double volume = 4.0 * M_PI * r * r * r / 3;
    double ans = volume * n;
    rep(i, n){
        cin >> x[i] >> y[i] >> z[i];
    }

    rep(i, n - 1){
        ll a = abs(x[i] - x[i + 1]);
        ll b = abs(y[i] - y[i + 1]);
        ll c = abs(z[i] - z[i + 1]);
        double d = sqrt(a * a + b * b);
        d = sqrt(d * d + c * c);

        double intersection = 2.0 / 3.0 * M_PI * ((r - d / 2) * (r - d / 2)) * (2.0 * r + d / 2);
        ans -= intersection;
    }

    ll a = abs(x[n - 1] - x[0]);
    ll b = abs(y[n - 1] - y[0]);
    ll c = abs(z[n - 1] - z[0]);
    double d = sqrt(a * a + b * b);
    d = sqrt(d * d + c * c);

    double intersection = 2.0 / 3.0 * M_PI * ((r - d / 2) * (r - d / 2)) * (2.0 * r + d / 2);
    ans -= intersection;

    cout << fixed << setprecision(10) << ans << endl;
}