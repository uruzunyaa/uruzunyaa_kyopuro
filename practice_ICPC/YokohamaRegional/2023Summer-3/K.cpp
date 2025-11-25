#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PLL = pair<ll, ll>;
using PPLL = pair<ll, PLL>;
#define vl vector<ll>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, m, n) for (ll i = m; i <= n; ++i)
const ll mod = 998244353;
const ll INF = 1LL << 60;

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

	// 履歴を全部消す(オプション)
	void snapshot(){
		while (history.size())history.pop();
	}

	// 初期状態またはsnapshotをした瞬間まで戻る
	void rollback(){
		while (history.size())undo();
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

int main(){
	ll n,m,q;
	cin>>n>>m>>q;
	OfflineDynamicConnectivity odc(2*n,q+1);
	set<pair<ll,ll>> check;
	rep(i,m){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		if(u>v)swap(u,v);
		odc.insert(0,u+n,v);
		odc.insert(0,u,v+n);
		check.insert({u,v});
	}

	vl t(q+1,0),x(q+1,0),y(q+1,0);

	loop(i,1,q){
		cin>>t[i]>>x[i]>>y[i];
		x[i]--,y[i]--;
		if(x[i]>y[i])swap(x[i],y[i]);

		if(t[i]==1){
			if(check.count({x[i],y[i]})){
				odc.erase(i,x[i]+n,y[i]);
				odc.erase(i,x[i],y[i]+n);
				check.erase({x[i],y[i]});
			}else{
				odc.insert(i,x[i]+n,y[i]);
				odc.insert(i,x[i],y[i]+n);
				check.insert({x[i],y[i]});
			}
		}
	}
	
	//辺の追加削除を確定させる
	odc.build();

	odc.run([&](int time){
		if(t[time]==2){

			//全頂点が連結か
			ll oksiz;
			if(odc.issame(0,n))oksiz=2*n;
			else oksiz=n;
			if(odc.size(0)!=oksiz){
				cout<<"No"<<endl;
				return;
			}

			//残り偶数個にするようなウォークがあるか判定
			bool check=false;
			if(n%2==1){
				if(odc.issame(x[time],y[time]))check=true;
			}else{
				if(odc.issame(x[time],y[time]+n))check=true;
			}
			if(check)cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
			return;
		}
	});
	return 0;
}