#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (long long i = 0; i < n; i++)
#define ll long long
#define vl vector<long long>
#define pb push_back

// 座標圧縮を行う関数
vector<int> compress_coordinates(vector<pair<int, pair<int, int>>> &intervals, map<int, int> &coord_map) {
    set<int> points;
    for (const auto &interval : intervals) {
        points.insert(interval.second.first);
        points.insert(interval.second.second);
    }

    vector<int> sorted_points(points.begin(), points.end());
    for (size_t i = 0; i < sorted_points.size(); ++i) {
        coord_map[sorted_points[i]] = i;
    }

    return sorted_points;
}

// ビットセットの構築関数
void build_bitsets(vector<pair<int, pair<int, int>>> &intervals, map<int, int> &coord_map, vector<bitset<1000>> &bitsets) {
    for (const auto &interval : intervals) {
        int typ = interval.first;
        int start = coord_map[interval.second.first];
        int end = coord_map[interval.second.second];

        for (int i = start; i <= end; ++i) {
            bitsets[typ].set(i);
        }
    }
}

// 共通区間の長さを計算する関数
int common_interval_length(vector<bitset<1000>> &bitsets, vector<int> &sorted_points, int typ_a, int typ_b) {
    bitset<1000> common_bits = bitsets[typ_a] & bitsets[typ_b];
    int total_length = 0;
    for (size_t i = 0; i < common_bits.size() - 1; ++i) {
        if (common_bits.test(i)) {
            total_length += sorted_points[i + 1] - sorted_points[i];
        }
    }
    return total_length;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> intervals;
    rep(i,m)
	rep(i, m / 2) {
        int t, p1, p2;
        cin >> t >> p1 >> p2;
        intervals.push_back({t, {p1, p2}});
    }

    ll q;
    cin >> q;
    vector<pair<int, int>> queries(q);
    rep(i, q) {
        cin >> queries[i].first >> queries[i].second;
    }

    // 座標圧縮
    map<int, int> coord_map;
    vector<int> sorted_points = compress_coordinates(intervals, coord_map);

    // ビットセットの初期化 (ここでは区間の数を1000と仮定しています)
    vector<bitset<1000>> bitsets(n + 1);

    // ビットセットの構築
    build_bitsets(intervals, coord_map, bitsets);

    // クエリの処理と出力
    rep(i, q) {
        int typ_a = queries[i].first;
        int typ_b = queries[i].second;
        int result = common_interval_length(bitsets, sorted_points, typ_a, typ_b);
        cout << result << endl;
    }

    return 0;
}
