#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

int main() {
    int n, m;
    cin >> n >> m;

    map<int, int> xCnt;
    map<int, int> yCnt;

    vector<P> ans;
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        xCnt[b]++;
        yCnt[a]++;
        ans.emplace_back(b, a);
    }

    loop(y,1, n) {
        if (m <= yCnt[y]) {
            continue;
        }
        int left = m - yCnt[y];

        rep(j, left) {
			ll x = y + (n / left + 1 * j) % n + 1;
			while(m <= xCnt[x]) x = (x + n / left + 1) % n + 1;
            ans.emplace_back(x, y);
            yCnt[y]++;
            xCnt[x]++;
        }

        y++;
    }

    cout << ans.size() << endl;
    for (auto p : ans) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
