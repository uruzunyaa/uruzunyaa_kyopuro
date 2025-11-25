#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll n; cin >> n;
    vector<PLL> pos(n);
    rep(i, n) {
        cin >> pos[i].first >> pos[i].second;
    }

    sort(pos.begin(), pos.end());
    ll ans = 0;

    vector<ll> rightMax(n + 1, -INF);
    vector<ll> rightMin(n + 1, INF);
    for (ll i = n - 1; i >= 0; --i) {
        rightMax[i] = max(rightMax[i + 1], pos[i].second);
        rightMin[i] = min(rightMin[i + 1], pos[i].second);
    }
    vector<ll> canRightV(n + 1, 0);
    {
        ll nowmx = -INF;
        for (ll i = n - 1; i >= 0; --i) {
            canRightV[i] = canRightV[i + 1];
            if (nowmx < pos[i].second) {
                canRightV[i]++;
                nowmx = pos[i].second;
            }
        }
    }

    ll nowmn = INF;
    ll nowmx = -INF;
    rep(i, n) {
        nowmx = max(nowmx, pos[i].second);
        if (pos[i].second > nowmn) continue;
        nowmn = pos[i].second;

        // 右からのnowmnを下回らない最大の左
        ll mnL = 0, mnR = n;
        if (rightMin[mnL] >= nowmn) {
            mnR = 0;
        }
        else {
            while (mnR - mnL > 1) {
                ll mid = (mnL + mnR) / 2;
                if (rightMin[mid] >= nowmn) mnR = mid;
                else mnL = mid;
            }
        }

        ll canL = max(mnR, i + 1);

        // 今の点から、nowmxを上回る最大の右
        ll mxL = i, mxR = n;
        if (rightMax[mxL] < nowmx) {
            // Do nothing
        }
        else {
            while (mxR - mxL > 1) {
                ll mid = (mxL + mxR) / 2;
                if (rightMax[mid] < nowmx) mxR = mid;
                else mxL = mid;
            }
        }

        ll canR = mxL;

        if (canR >= canL) {
            ans += canRightV[canL] - canRightV[canR + 1];
        } 
    }

    cout << ans << endl;
}