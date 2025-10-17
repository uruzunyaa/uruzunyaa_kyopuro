#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

struct ATK
{
    // 初期値
    ll a;
    // K倍されるごとの追加分
    ll b;
    // 何人いるか
    ll cnt;
};

int main() {
    ll n, d, h;
    cin >> n >> d >> h;
    map<ll, ATK> ks;

    rep(i, n) {
        ll a;
        cin >> a;
        ll need = (d + a - 1) / a;
        ks[need].a += need * a - d;
        ks[need].b += a;
        ks[need].cnt++;
    }

    map<ll, ll> ATK1;

    ll allCnt = 0;
    for (auto it = ks.rbegin(); it != ks.rend(); it++) {
        ATK1[it->first] = allCnt;
        // cout << it->first << " " << allCnt << endl;
        allCnt += it->second.cnt;
    }

    // cout << "---------" << endl;

    // 攻撃力1の人だけで倒せるとき
    if (allCnt >= h) {
        cout << 1 << endl;
        return 0;
    }

    ll allA = 0;
    ll allB = 0;
    ll dmg = 0;
    ll prevK = 0;
    ll minK = 1001001001001;
    for (auto it = ks.begin(); it != ks.end(); it++) {
        ll k = it->first;
        dmg += allB * (k - prevK);
        allA += it->second.a;
        allB += it->second.b;
        // cout << k << " " << it->second.a << " " << it->second.b << " "
        // << ((h - allA - ATK1[k] - dmg) + allB - 1) / allB << endl;

        // a + bx + 今までのダメージ + 1ダメの人 >= h
        // のxを求める式で、さらに切り上げたもの。それに、本来ずれているはずのkを足す
        minK = min(minK, k + ((h - allA - ATK1[k] - dmg) + allB - 1) / allB);
        prevK = k;
    }
    cout << minK << endl;
    return 0;
}
