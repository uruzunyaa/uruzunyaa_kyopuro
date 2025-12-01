#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    string ans = "";
    ll base = 1;

    cout << "query 0" << endl;
    ll target;
    cin >> target;

    rep(digit, 18) {
        ll l = 0, r = 10;
        while (r - l > 1) {
            ll mid = (l + r) / 2;
            cout << "query " << mid * base << endl;
            ll res; cin >> res;
            if (res <= target) {
                r = mid;
            }
            else {
                l = mid;
            }
        }

        ans.push_back('0' + (10 - r));
        base *= 10;
    }

    reverse(ans.begin(), ans.end());
    cout << "answer " << stoll(ans) << endl;
}