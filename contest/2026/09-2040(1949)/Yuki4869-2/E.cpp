//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


struct UnionFindUndo{
	vector<int> data;
	stack<pair<int, int>> history;
	int ConnectedComponent;
	stack<int> cmphis;

	UnionFindUndo(int sz){
		data.assign(sz, -1);
		ConnectedComponent=sz;
	}

	// 頂点xとyを結合
	bool unite(int x, int y){
		x = find(x), y = find(y);
		history.emplace(x, data[x]);
		history.emplace(y, data[y]);
		cmphis.push(ConnectedComponent);
		if (x == y)return (false);
		if (data[x] > data[y])swap(x, y);
		data[x] += data[y];
		data[y] = x;
		ConnectedComponent--;
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
		ConnectedComponent=cmphis.top();
		cmphis.pop();
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
	int connected_component(){
		return uf.ConnectedComponent;
	}
};


// Union-Find
struct UnionFind {
	int cmp;
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1), cmp(n){ }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return par[x] = root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	// x を含むグループと y を含むグループとを併合する
	bool unite(int x, int y) {
		x = root(x), y = root(y);
		if (x == y) return false; 
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		cmp--;
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};



//メイン
int main(){
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	ll n,m;
	cin>>n>>m;
	
	vector<unordered_set<ll>> st(n);
	vl u(m),v(m),l(m,5);
	rep(i,m){
		cin>>u[i]>>v[i];
		u[i]--,v[i]--;
		st[u[i]].insert(i);
		st[v[i]].insert(i);
	}
	ll q;
	cin>>q;
	
	vvl er;
	er.push_back({0,0,0});
	
	loop(i,1,q){
		ll t,a;
		cin>>t>>a;
		a--;
		if(t==1){
			unordered_set<ll> nst;
			for(auto &val:st[a]){
				l[val]--;
				if(l[val]==0){
					er.push_back({i,u[val],v[val]});
				}else{
					nst.insert(val);
				}
			}
			swap(st[a],nst);
		}else{
			if(l[a]>0)l[a]++;
		}
	}

	UnionFind uf(n);

	rep(i,m){
		if(l[i]==0)continue;
		uf.unite(u[i],v[i]);
	}

	
	vl ans;
	rloop(i,q,1){
		ans.push_back(uf.cmp);
		while(er.back()[0]==i){
			uf.unite(er.back()[1],er.back()[2]);
			er.pop_back();
		}
	}

	reverse(ans.begin(),ans.end());
	
	rep(i,q)cout<<ans[i]<<'\n';
	return 0;
}
