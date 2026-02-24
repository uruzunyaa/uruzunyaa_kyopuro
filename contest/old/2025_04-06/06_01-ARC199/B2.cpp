#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i = 0; i < (ll)(n); i++)
#define rrep(i,n) for (ll i = (n) - 1; i >= 0; i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a)    \
    rep(ii, a.size()) { cout << a[ii] << " "; } \
    cout << "\n"
#define inf 4000000000000000000LL

random_device rnd;               // 非決定的な乱数生成器
mt19937 mt(rnd());               // メルセンヌ・ツイスタの32ビット版

struct XorBasis {
    vector<ll> basis;
    vector<vl> used;
    int n;

    XorBasis(int n_) : n(n_) {}

    void add(ll x, const vl& bits) {
        vl tmp = bits;
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) {
                    tmp[j] ^= used[i][j];
                }
            }
        }
        if (x != 0) {
            basis.push_back(x);
            used.push_back(tmp);
        }
    }

    // x が basis から作れるか、作れるなら res に使った元のベクトルの組み合わせが入る
    pair<bool, vl> represent(ll x) const {
        vl res(n, 0);
        for (int i = 0; i < (int)basis.size(); ++i) {
            if ((x ^ basis[i]) < x) {
                x ^= basis[i];
                for (int j = 0; j < n; ++j) {
                    res[j] ^= used[i][j];
                }
            }
        }
        return { x == 0, res };
    }
};

void solve() {
    ll n, k;
    cin >> n >> k;
    vl orig_a(n);
    rep(i, n) cin >> orig_a[i];

    bool solution_found = false;
    vl best_ans;

    // 0回目: 元の順序で試す
    // 1回目: 配列をシャッフルして再度試す
    for (int attempt = 0; attempt < 10 && !solution_found; ++attempt) {
        vl a = orig_a;
        if (attempt == 1) {
            shuffle(a.begin(), a.end(), mt);
        }

        // ===== XorBasis の構築 =====
        XorBasis xb(n);
        for (int i = 0; i < n; ++i) {
            vl bits(n, 0);
            bits[i] = 1;
            xb.add(a[i], bits);
        }

        // k を表現できるかどうか調べる
        auto [ok, used] = xb.represent(k);
        if (!ok) {
            // この順序だとそもそも k が作れない → 次の試行へ
            continue;
        }

        // k が a[0] と同じなら、操作不要
        if (k == a[0]) {
            solution_found = true;
            best_ans.clear();
            break;
        }

        // 操作列の構築
        vl ans;
        ll okind = inf;

        // まず後ろから「used の並び合わせ」を探す
        rrep(i, n - 1) {
            if (used[i] == used[i + 1]) {
                // 同じならペアを使って操作を構築
                if (used[i] == 0) {
                    // bits[i] = 0 の場合の処理
                    ans.push_back(i);
                    ans.push_back(i);
                    for (ll j = i + 2; j < n; j += 2) {
                        // 前を掃除
                        for (ll l = i + 2; l < j; l += 2) {
                            ans.push_back(l);
                            ans.push_back(l);
                        }
                        for (ll l = j - 1; l > i; --l) {
                            ans.push_back(l);
                        }
                    }
                    ans.push_back(i);
                    okind = i;
                    break;
                } else {
                    // bits[i] = 1 の場合の処理
                    ans.push_back(i);
                    if (i == n - 2) {
                        okind = i;
                        break;
                    }
                    i++;
                    ans.push_back(i);
                    ans.push_back(i);
                    for (ll j = i + 2; j < n; j += 2) {
                        for (ll l = i + 2; l < j; l += 2) {
                            ans.push_back(l);
                            ans.push_back(l);
                        }
                        for (ll l = j - 1; l > i; --l) {
                            ans.push_back(l);
                        }
                    }
                    ans.push_back(i);
                    ans.push_back(i - 1);
                    okind = i - 1;
                    break;
                }
            }
        }

        ll freedom = n - (ll)xb.basis.size();
        if (okind == inf && freedom == 0) {
            // 自由度もなく、okind も見つけられなかった → この順序では失敗
            continue;
        }

        // okind より前にビットを整える操作を加える
        if (okind != inf) {
            rrep(i, okind) {
                if (used[i] == 1) {
                    ans.push_back(i);
                } else {
                    ans.push_back(i);
                    ans.push_back(i);
                    ans.push_back(i + 1);
                    ans.push_back(i);
                }
            }
        }

        // ここまで来たら解が見つかった
        solution_found = true;
        best_ans = ans;
    }

    if (!solution_found) {
        cout << "No\n";
        return;
    }

    // 解が見つかっていれば出力。best_ans の中身を 1-based index に変換して出力する
    cout << "Yes\n";
    cout << best_ans.size() << "\n";
    rep(i, best_ans.size()) {
        cout << (best_ans[i] + 1) << (i + 1 < best_ans.size() ? ' ' : '\n');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
