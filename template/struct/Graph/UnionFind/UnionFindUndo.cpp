#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, m, n) for (ll i = m; i <= n; ++i)
#define vl vector<ll>
#define vvl vector<vl>

//巻き戻し可能UnionFind
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

int main(){

}