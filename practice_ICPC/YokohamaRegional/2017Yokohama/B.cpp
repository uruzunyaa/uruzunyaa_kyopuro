#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
#define rep(i, n) for(ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for(ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;



int main() {
    ll m;
    cin >> m;
    vector<pair<ll,ll>> x_y(m);
    rep(i, m){
        cin >> x_y[i].first >> x_y[i].second;
    }


    ll ans = 0;
    for(ll bit = 0; bit < (1 << m); bit++){
        if (bit % 1000 == 0) cout << bit << endl;
        if(__popcount(bit) * 2 != m)continue;
        vector<ll> ones,zeros;
        rep(i, m){
            if(bit & (1 << i)){
                ones.emplace_back(i);
            }
            else {
                zeros.emplace_back(i);
            }
        }

        do{
            // unordered_map<double,ll> angles;
            ll cnt = 0;
            const double inf = 1000000000;
            rep(i, ones.size()) {
                ll point1_x = x_y[ones[i]].first;
                ll point1_y = x_y[ones[i]].second;
                ll point2_x = x_y[zeros[i]].first - point1_x;
                ll point2_y = x_y[zeros[i]].second - point1_y;
                point1_x = 0;
                point1_y = 0;

                double angle1;
                if (point2_x == 0) angle1 = inf;
                else angle1 = (double)point2_y / point2_x;

                rep(j, i) {
                    ll point21_x = x_y[ones[j]].first;
                    ll point21_y = x_y[ones[j]].second;
                    ll point22_x = x_y[zeros[j]].first - point21_x;
                    ll point22_y = x_y[zeros[j]].second - point21_y;
                    point21_x = 0;
                    point21_y = 0;

                    double angle2;
                    if (point22_x == 0) angle2 = inf;
                    else angle2 = (double)point22_y / point22_x;

                    if (angle1 == angle2) cnt++;
                }
            }

            // rep(i, ones.size()){
            //     ll point1_x = x_y[ones[i]].first;
            //     ll point1_y = x_y[ones[i]].second;
            //     ll point2_x = x_y[zeros[i]].first - point1_x;
            //     ll point2_y = x_y[zeros[i]].second - point1_y;
            //     point1_x = 0;
            //     point1_y = 0;

            //     const double inf = 1000000000;
            //     if(point2_x == 0){
            //         ll oldcnt = angles[inf];
            //         if (2 <= oldcnt) {
            //             cnt -= oldcnt * (oldcnt - 1) / 2;
            //         }
            //         ll newcnt = ++angles[inf];
            //         if (2 <= newcnt) {
            //             cnt += newcnt * (newcnt - 1) / 2;
            //         }
            //         // cout << 1000000000 << endl;
            //     }
            //     else {
            //         double angle = (double)point2_y / point2_x;
            //         ll oldcnt = angles[angle];
            //         if (2 <= oldcnt) {
            //             cnt -= oldcnt * (oldcnt - 1) / 2;
            //         }
            //         ll newcnt = ++angles[angle];
            //         if (2 <= newcnt) {
            //             cnt += newcnt * (newcnt - 1) / 2;
            //         }
            //         // cout << (double)point2_y / point2_x << " ";
            //     }
            // }
            // cout << endl;
            ans = max(ans, cnt);
        }while(next_permutation(zeros.begin(),zeros.end()));
    }
    cout << ans << endl;
    return 0;
}