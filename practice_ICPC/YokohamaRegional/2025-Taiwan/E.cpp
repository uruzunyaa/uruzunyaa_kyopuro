#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
constexpr ll INF = 9009009009009009009LL;

int main() {
    ll T;
    cin >> T;
    while(T--){
        string s;
        ll j, k;
        cin >> s >> j >> k;
        j--;
        k--;
        string t = s;
        rep(i, j){
            next_permutation(s.begin(), s.end());
        }
        rep(i, k){
            next_permutation(t.begin(), t.end());
        }
        ll A = 0;
        rep(i, s.length()){
            if(s[i] == t[i])A++;
        }
        cout << A << "A" << s.length() - A << "B\n";
    }
}