#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using P = pair<int, int>;
using PLL = pair<ll, ll>;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)
const ll INF = 1001001001001001001LL;

template <class T> inline bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> inline bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int main() {
    ll h, w;
    cin >> h >> w;
    unordered_map<char, vector<P>> animalMap;
    vector<vector<char>> grid(h, vector<char>(w));
    rep(i, h) rep(j, w) {
        cin >> grid[i][j];
        animalMap[grid[i][j]].push_back({i, j});
    }

    ll n;
    cin >> n;
    vector<unordered_set<char>> eater(26, unordered_set<char>());
    vector<unordered_set<char>> rEater(26, unordered_set<char>());
    rep(i, n) {
        char p, v;
        cin >> p >> v;
        eater[p - 'a'].insert(v);
        rEater[v - 'a'].insert(p);
    }

    set<char> done;
    rep(i, animalMap.size()) {
        char current = '\0';
        for (const auto [animal, _] : animalMap) {
            if (done.count(animal)) continue;

            bool ok = true;
            for (const auto need : rEater[animal - 'a']) {
                if (!done.count(need)) {
                    ok = false;
                    break;
                }
            }

            if (ok){
				current = animal;
				break;
			}
        }

        for (const auto [y, x] : animalMap[current]) {
            if (grid[y][x] == '-') continue;
            rep(i, 8) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || w <= nx || ny < 0 || h <= ny) continue;
                if (eater[current - 'a'].count(grid[ny][nx])) {
                    grid[ny][nx] = '-';
                }
            }
        }

        done.insert(current);
    }

    rep(i, h) {
        rep(j, w) {
            cout << ""s + grid[i][j];
            if (j != w - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
