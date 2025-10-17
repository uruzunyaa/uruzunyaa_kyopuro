#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll k;
    cin >> k;

    const ll MAX = sqrt(k);
    for (ll m = MAX; m > 0; --m) {
        for (ll n = m - 1; n > 0; --n) {
            if (m % 2 == n % 2 || gcd(m, n) != 1) continue;

            ll a = m * m - n * n;
            ll b = 2 * m * n;
            ll c = m * m + n * n;

            if (k % a == 0 || k % b == 0 || k % c == 0) {
                if (b < a) swap(a, b);
                cout << "Yes" << endl;
                cout << a << " " << b << " " << c << endl;
            }
        }
    }

    cout << "No" << endl;
    return 0;
}
