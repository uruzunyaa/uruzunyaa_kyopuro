#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < (ll)n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
constexpr ll INF = 9009009009009009009LL;

template <typename T>
vector<vector<T>> rotation(vector<vector<T>> &g) {
    ll h = g[0].size();
    ll w = g.size();
    vector<vector<T>> res(h, vector<T>(w));

    rep(i, h) rep(j, w) {
        res[i][j] = g[w - j - 1][i];
    }
    return res;
}
vector<string> rotation(vector<string> &g) {
    ll h = g[0].size();
    ll w = g.size();
    vector<string> res(h, string(w, '.'));

    rep(i, h) rep(j, w) {
        res[i][j] = g[w - j - 1][i];
    }
    return res;
}

struct Cell {
    char val;
    ll x, y;

    Cell() : val('\0'), x(INF), y(INF) {}
    Cell(char val, ll x, ll y) : val(val), x(x), y(y) {}
};

int main() {
    ll h, w; cin >> h >> w;
    vector<string> g1(h);
    rep(i, h) cin >> g1[i];
    ll H, W; cin >> H >> W;
    vector<string> target(H);
    rep(i, H) cin >> target[i];

    vector<vector<Cell>> src(h, vector<Cell>(w));
    rep(i, h) rep(j, w) {
        src[i][j] = Cell(g1[i][j], j, i);
    }


    
    // 外周のxを削る
    rep(rot, 4) {
        // 下からpopbackする src
        for (int i = src.size() - 1; i >= 0; --i) {
            bool ok = true;
            rep(j, src[0].size()) {
                if (src[i][j].val == 'o') {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
            src.pop_back();
        }
        // 下からpopbackする target
        for (int i = target.size() - 1; i >= 0; --i) {
            bool ok = true;
            rep(j, target[0].size()) {
                if (target[i][j] == 'o') {
                    ok = false;
                    break;
                }
            }
            if (!ok) break;
            target.pop_back();
        }

        src = rotation(src);
        target = rotation(target);
    }


    // 削らない場合
    // targetを回転させる
    rep(trot, 4) {
        // srcを回転させる
        rep(rot2, 4) {
            ll sh = src.size(), sw = src[0].size();
            ll th = target.size(), tw = target[0].size();
            vector<vector<Cell>> scopy = src;

            // もしsrcがtargetのサイズより大きければ飛ばす
            if (th < sh || tw < sw) {
                src = rotation(src);
                continue;
            }

            // 右に拡張したとき、(rot + rot2) % 4がずれる座標の値
            constexpr int dx[4] = {1, 0, -1, 0};
            constexpr int dy[4] = {0, -1, 0, 1};
            const ll RIGHT = (rot2) % 4;
            const ll DOWN = (rot2 + 3) % 4;

            // targetの左上に合わせたいので、右下に向かってsrcを拡張する
            // まず、今のsrcの横幅を拡張する
            rep(i, sh) {
                rep(j, tw - sw) {
                    src[i].push_back(Cell('x', src[i].back().x + dx[RIGHT], src[i].back().y + dy[RIGHT]));
                }
            }
            // srcの下に拡張する
            rep(i, th - sh) {
                src.push_back(vector<Cell>());
                src.back().push_back(Cell('x', src[sh + i - 1][0].x + dx[DOWN], src[sh + i - 1][0].y + dy[DOWN]));
                rep(j, tw - 1) {
                    src.back().push_back(Cell('x', src.back()[j].x + dx[RIGHT], src.back()[j].y + dy[RIGHT]));
                }
            }
            assert(src.size() == th && src[0].size() == tw);
            // srcとtargetを比較して2つ違う場所を探す
            Cell from, to;
            bool ok = true;
            rep(i, th) {
                rep(j, tw) {
                    if (src[i][j].val != target[i][j]) {
                        // fromの場合はsrcがo
                        if (src[i][j].val == 'o') {
                            if (from.val == '\0') {
                                from = src[i][j];
                            }
                            else {
                                ok = false;
                                break;
                            }
                        }
                        else {
                            if (to.val == '\0') {
                                to = src[i][j];
                            }
                            else {
                                ok = false;
                                break;
                            }
                        }
                    }
                }
                if (!ok) break;
            }

            // もし見つかったら終わり
            if (ok && from.val != '\0' && to.val != '\0') {
                cout << from.x << " " << from.y << endl;
                cout << to.x << " " << to.y << endl;
                return 0;
            }

            src = scopy;
            src = rotation(src);
        }

        target = rotation(target);
    }


    // 削る場合
    rep(rot, 4) {
        // srcの一番下を削ることを考える
        ll cnt = 0;
        Cell from;
        rep(j, w) {
            if (src[src.size() - 1][j].val == 'o') {
                cnt++;
                from = src[src.size() - 1][j];
            }
        }
        // 一番下のoが1個じゃなければ削る意味がないので飛ばす
        if (cnt != 1) {
            src = rotation(src);
            continue;
        }

        // 後で戻すために一番下を保管
        vector<Cell> tmp = src.back();
        src.pop_back();

        rep(trot, 4) {
            // 削ったsrcを回転させる
            rep(rot2, 4) {
                ll sh = src.size(), sw = src[0].size();
                ll th = target.size(), tw = target[0].size();
                vector<vector<Cell>> scopy = src;

                // もしsrcがtargetのサイズより大きければ飛ばす
                if (th < sh || tw < sw) {
                    src = rotation(src);
                    continue;
                }

                // 右に拡張したとき、(rot + rot2) % 4がずれる座標の値
                constexpr int dx[4] = {1, 0, -1, 0};
                constexpr int dy[4] = {0, -1, 0, 1};
                const ll RIGHT = (rot + rot2) % 4;
                const ll DOWN = (rot + rot2 + 3) % 4;

                // targetの左上に合わせたいので、右下に向かってsrcを拡張する
                // まず、今のsrcの横幅を拡張する
                rep(i, sh) {
                    rep(j, tw - sw) {
                        src[i].push_back(Cell('x', src[i].back().x + dx[RIGHT], src[i].back().y + dy[RIGHT]));
                    }
                }
                // srcの下に拡張する
                rep(i, th - sh) {
                    src.push_back(vector<Cell>());
                    src.back().push_back(Cell('x', src[sh + i - 1][0].x + dx[DOWN], src[sh + i - 1][0].y + dy[DOWN]));
                    rep(j, tw - 1) {
                        src.back().push_back(Cell('x', src.back()[j].x + dx[RIGHT], src.back()[j].y + dy[RIGHT]));
                    }
                }
                assert(src.size() == th && src[0].size() == tw);
                // srcとtargetを比較して唯一違う場所を探す
                Cell diff;
                bool ok = true;
                rep(i, th) {
                    rep(j, tw) {
                        if (src[i][j].val != target[i][j]) {
                            if (diff.val == '\0') {
                                diff = src[i][j];
                            }
                            else {
                                ok = false;
                                break;
                            }
                        }
                    }
                    if (!ok) break;
                }

                // もし見つかったら終わり
                if (ok && diff.val != '\0') {
                    // cout << rot << " " << rot2 << endl;
                    // rep(i, th) {
                    //     rep(j, tw) {
                    //         cout << "[" << src[i][j].val << "," << src[i][j].x << "," << src[i][j].y << "] ";
                    //     }
                    //     cout << endl;
                    // }
                    cout << from.x << " " << from.y << endl;
                    cout << diff.x << " " << diff.y << endl;
                    return 0;
                }

                src = scopy;
                src = rotation(src);
            }

            target = rotation(target);
        }

        src.push_back(tmp);
        src = rotation(src);
    }

    throw runtime_error("not found");
    return 0;
}