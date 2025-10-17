#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    string s;
    cin >> s;

    set<string> cnt;

    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 0; j <= s.size() - i; ++j) {
            string subs = s.substr(j, i);
            cnt.insert(subs);
        }
    }

    cout << cnt.size() << endl;
    return 0;
}
