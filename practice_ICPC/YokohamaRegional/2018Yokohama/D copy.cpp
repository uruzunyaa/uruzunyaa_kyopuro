#include <bits/stdc++.h>
using namespace std;
using ll = int;
#define rep(i, n) for(ll i = 0; i < n; i++)
// constexpr ll INF = 9009009009009009009LL;
constexpr int INF = 2002002002;

struct Data {
    ll len;
    ll prevP;
    ll prevQ;
    ll sameLen;
};

int main(){
    string p, q; cin >> p >> q;
    reverse(p.begin(), p.end());
    reverse(q.begin(), q.end());
    p = 'S' + p + 'G';
    q = 'S' + q + 'G'; 

    vector<vector<ll>> p_prevmap(p.size(), vector<ll>(2));
    vector<vector<ll>> q_prevmap(q.size(), vector<ll>(2));
    ll prev0 = p.size() - 1, prev1 = p.size() - 1;
    for (ll i = p.size() - 1; i >= 0; --i) {
        p_prevmap[i][0] = prev0;
        p_prevmap[i][1] = prev1;
        if (p[i] == '0') prev0 = i;
        else prev1 = i;
    }
    prev0 = q.size() - 1, prev1 = q.size() - 1;
    for (ll i = q.size() - 1; i >= 0; --i) {
        q_prevmap[i][0] = prev0;
        q_prevmap[i][1] = prev1;
        if (q[i] == '0') prev0 = i;
        else prev1 = i;
    }

    vector<vector<Data>> dp(p.size(), vector<Data>(q.size(), {INF, -INF, -INF, -INF}));
    dp[0][0] = {0, 0, 0, 1};
    rep(i, p.size()) {
        rep(j, q.size()) {
            if (dp[i][j].len == INF) continue;
            rep(k, 2) {
                ll np = p_prevmap[i][k];
                ll nq = q_prevmap[j][k];
                Data now = dp[i][j];
                ll prevValue = p[now.prevP] - '0';
                Data next = {now.len + 1, i, j, prevValue == k ? now.sameLen + 1 : 1};

                if (next.len < dp[np][nq].len) {
                    dp[np][nq] = next;
                }
                else if (next.len == dp[np][nq].len) {
                    if (k != p[dp[np][nq].prevP] - '0') {
                        if (k == 0) {
                            dp[np][nq] = next;
                        }
                    }
                    else {
                        if (k == 0) {
                            if (next.sameLen > dp[np][nq].sameLen) {
                                dp[np][nq] = next;
                            }
                        }
                        else {
                            if (next.sameLen < dp[np][nq].sameLen) {
                                dp[np][nq] = next;
                            }
                        }
                    }
                }
            }
        }
    }



    string ans = "";
    for (Data now = dp[p.size() - 1][q.size() - 1]; now.prevP != 0; now = dp[now.prevP][now.prevQ]) {
        ans += p[now.prevP];
    }

    cout << ans << "\n";
}