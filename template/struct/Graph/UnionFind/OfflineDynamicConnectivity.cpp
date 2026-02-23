#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, m, n) for (ll i = m; i <= n; ++i)
#define vl vector<ll>
#define vvl vector<vl>

struct UnionFindUndo{
	vector<int> data;
	stack<pair<int, int>> history;

	UnionFindUndo(int sz){
		data.assign(sz, -1);
	}

	// 頂点xとyを結合
	bool unite(int x, int y){
		x = find(x), y = find(y);
		history.emplace(x, data[x]);
		history.emplace(y, data[y]);
		if (x == y)return (false);
		if (data[x] > data[y])swap(x, y);
		data[x] += data[y];
		data[y] = x;
		return (true);
	}

	// 頂点kのリーダーを返す
	int find(int k){
		if (data[k] < 0)return (k);
		return (find(data[k]));
	}

	//連結判定
	bool issame(int u,int v){
		return find(u)==find(v);
	}

	// 頂点kのサイズを求める
	int size(int k){
		return (-data[find(k)]);
	}

	// 1回分のuniteを取り消す
	void undo(){
		data[history.top().first] = history.top().second;
		history.pop();
		data[history.top().first] = history.top().second;
		history.pop();
	}
};

//UnionFindUndoを前提にクエリ先読み削除可能UF
struct OfflineDynamicConnectivity{
	using edge = pair<int, int>;

	UnionFindUndo uf;
	int N, T, segsz;
	vector<vector<edge>> seg;
	int comp;

	vector<pair<pair<int, int>, edge>> pend;
	map<edge, int> cnt, appear;

	//頂点数,時間軸の長さ(0-index)
	OfflineDynamicConnectivity(int N, int T) : uf(N), N(N), T(T), comp(N){
		segsz = 1;
		while (segsz < T)segsz <<= 1;
		seg.resize(2 * segsz - 1);
	}

	//時刻idxにuとvに辺を追加する(多重辺も行けるが、逆に無視はされない)
	void insert(int idx, int u, int v){
		auto e = minmax(u, v);
		if (cnt[e]++ == 0)appear[e] = idx;
	}

	//時刻idxにuとvの辺を削除する。(必ず時刻順にinsertより後に与える事)
	void erase(int idx, int s, int t){
		auto e = minmax(s, t);
		if (--cnt[e] == 0)pend.emplace_back(make_pair(appear[e], idx), e);
	}

	//build時に内部で使用してる関数
	void add(int a, int b, const edge &e, int k, int l, int r){
		if (r <= a || b <= l)return;

		if (a <= l && r <= b){
			seg[k].emplace_back(e);
			return;
		}
		add(a, b, e, 2 * k + 1, l, (l + r) >> 1);
		add(a, b, e, 2 * k + 2, (l + r) >> 1, r);
	}

	//クエリ先読みが終わったら実行
	void build(){
		for (auto &p : cnt){
			if (p.second > 0)pend.emplace_back(make_pair(appear[p.first], T), p.first);
		}
		for (auto &s : pend){
			add(s.first.first, s.first.second, s.second,0,0,segsz);
		}
	}

	//時刻順にfで与えた関数が呼ばれる。
	void run(const function<void(int)> &f, int k = 0){
		int add = 0;
		for (auto &e : seg[k]){
			add += uf.unite(e.first, e.second);
		}
		comp -= add;
		if (k < segsz - 1){
			run(f, 2 * k + 1);
			run(f, 2 * k + 2);
		}
		else if (k - (segsz - 1) < T){
			int query_index = k - (segsz - 1);
			f(query_index);
		}
		for (auto &e : seg[k]){
			uf.undo();
		}
		comp += add;
	}

	//連結判定(UndoUnionFind側のを呼び出すだけ)
	bool issame(int u, int v){
		return uf.issame(u,v);
	}

	// 頂点uが属する成分のサイズを取得(UndoUnionFind側の実装を呼んでる)
	int size(int u){
		return uf.size(u);
	}
};

//使い方
int main(){
	//OfflineDynamicConnectivity odc(頂点数,時間数);
	//odc.insert(追加時刻,頂点u,頂点v)
	//odc.erase(削除時刻,頂点u,頂点v)
	//odc.build();

	/*
	odc.run([&](int time){
		時刻 time でしたい処理
		
	});
	*/
}