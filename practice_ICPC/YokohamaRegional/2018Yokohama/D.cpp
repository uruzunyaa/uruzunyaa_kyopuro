#include <bits/stdc++.h>
using namespace std;
using ll = short;
#define rep(i, n) for(ll i = 0; i < n; i++)
// constexpr ll INF = 9009009009009009009LL;
constexpr short INF = 32000;

struct Data {
    ll len;
    ll prevP;
    ll prevQ;
    ll nowValue;
    ll prevValue;
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

    vector<vector<Data>> dp(p.size(), vector<Data>(q.size(), {INF, -INF, -INF, INF, INF, -INF}));
    dp[0][0] = {0, -INF, -INF, INF, INF, 0};
    rep(i, p.size()) {
        rep(j, q.size()) {
            if (dp[i][j].len == INF) continue;
            rep(k, 2) {
                ll np = p_prevmap[i][k];
                ll nq = q_prevmap[j][k];
                Data now = dp[i][j];
                Data next = {(short)(now.len + 1), i, j, k, now.nowValue, now.prevValue == now.nowValue ? (short)(now.sameLen + 1) : (short)1};

				//長さで最小値が更新される。
                if (next.len < dp[np][nq].len) {
                    dp[np][nq] = next;
                }
                else if (next.len == dp[np][nq].len) {
					//ゴールの時に、ここに来るのにより小さい方を選んでる物を採用
                    if(next.nowValue != dp[np][nq].nowValue){
						if(next.nowValue==0){
							dp[np][nq] = next;
						}
					//直前の
					}else if (next.prevValue != dp[np][nq].prevValue) {
                        if (next.prevValue == 0) {
                            dp[np][nq] = next;
                        }
                    }
                    else {
                        if (next.prevValue == 0) {
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
    for (Data now = dp[p.size() - 1][q.size() - 1]; now.nowValue != INF; now = dp[now.prevP][now.prevQ]) {
        ans += now.nowValue + '0';
    }

    cout << ans << "\n";
}