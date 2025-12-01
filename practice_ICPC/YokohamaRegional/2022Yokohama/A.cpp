#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n), b(n);
    vector<pair<ll, ll>> ab(n);
    ll now = 100;
    rep(i, n){
        cin >> a[i] >> b[i];
        ab[i] = {a[i], b[i]};
        now = min(now, a[i]);
    }

    vector<bool> used(n, false);
    vector<ll> ans(n, 0);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;

    ll count = 0;
    while(count < n || !q.empty()){
        rep(i, n){
            if(ab[i].first <= now && !used[i]){
                q.push({ab[i].second - ab[i].first, i});
                used[i] = true;
                count++;
            }
        }
        ll cnt = 0;
        while(!q.empty() && cnt < k){
            auto [remaining, id] = q.top();
            ans[id] = now;
            q.pop();
            cnt++;
        }

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> temp;
        while(!q.empty()){
            temp.push({q.top().first - 1, q.top().second});
            q.pop();
        }
        swap(q, temp);
        now++;
    }
    rep(i, n){
        cout << ans[i] << '\n';
    }
    return 0;
}