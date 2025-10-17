#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    ll n;
    cin >> n;

    string s = "";
    loop(i, 1, n) {
        if (i % 3 == 0) s += "x";
        else s += "o";
    }

    cout << s << endl;

    return 0;
}
