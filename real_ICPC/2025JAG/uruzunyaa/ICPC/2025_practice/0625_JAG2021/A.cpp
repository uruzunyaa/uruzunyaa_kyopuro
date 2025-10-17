#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};

int solve() {
    ll n;
    cin >> n;
	if(n == 0){return 1;}
    map<ll,ll> medal_cnt;
    map<ll,ll> gold_cnt;
    ll maxmedal = 0;
    ll maxgold = 0;
    rep(i, n){
        ll year;
        string name,medal;
        cin >> year >> name >> medal;
        medal_cnt[year]++;
        maxmedal = max(maxmedal,medal_cnt[year]);
        if(medal == "Gold"){
            gold_cnt[year]++;
            maxgold = max(maxgold,gold_cnt[year]);
        }
    }
    for(auto p : gold_cnt){
        if(p.second == maxgold){
            cout << p.first << " ";
            break;
        }
    }
    for(auto p : medal_cnt){
        if(p.second == maxmedal){
            cout << p.first << endl;
            break;
        }
    }
    return 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(solve() == 0);
    return 0;
}