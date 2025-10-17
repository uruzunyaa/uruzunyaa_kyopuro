#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    ll ans = 0;
    ll direction = 0;
    rep(i, s.length()){
        if(s[i] == 'R'){
            direction++;
        }else if(s[i] == 'L'){
            direction--;
        }
        if(direction == 4){
            ans++;
            direction = 0;
        }else if(direction == -4){
            direction = 0;
        }
    }
    cout << ans << endl;
    return 0;
}