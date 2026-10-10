//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
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


/**
 * @brief 強連結成分分解(Strongly Connected Components)
 * @details 強連結成分を1つのノードとして扱うグラフを再構築する
 * @note 新たなグラフはトポロジカル順になる
 */
struct SCC
{
  private:
	// 元の頂点数
	ll n;
	// G: 元のグラフ, rG: 逆辺を張ったグラフ
	vector<vector<ll>> G, rG;

	// order: トポロジカルソート
	vector<ll> order;

	// component: 各頂点が属する強連結成分の番号
	vector<ll> component;
	// component_size: 強連結成分のサイズ
	vector<ll> components_size;
	// component_count: 強連結成分の数
	ll component_count = 0;
	// component_elements: 各強連結成分に属する頂点のリスト
	vector<vector<ll>> component_elements;

	vector<vector<ll>> rebuildedG;

	// 1度目のDFSでトポロジカルソートを行う O(|V|+|E|)
	void topological_sort() {
		vector<bool> used(n, false);
		auto dfs = [&used, this](auto dfs, ll v) -> void {
			used[v] = 1;
			for (auto nv : G[v]) {
				if (!used[nv]) dfs(dfs, nv);
			}
			order.push_back(v);
		};

		rep(v, n) {
			if (!used[v]) dfs(dfs, v);
		}

		reverse(order.begin(), order.end());
	}
	// 2度目のDFSで逆辺のグラフでトポロジカル順に強連結成分を探す O(|V|+|E|)
	void search_components() {
		auto dfs = [this](auto dfs, ll v, ll k) -> void {
			component[v] = k;
			components_size[k]++;
			component_elements[k].push_back(v);
			for (auto nv : rG[v]) {
				if (component[nv] == -1) dfs(dfs, nv, k);
			}
		};

		for (auto v : order) {
			if (component[v] == -1) {
				components_size.push_back(0);
				component_elements.push_back(vector<ll>());
				dfs(dfs, v, component_count++);
			}
		}
	}
	/**
	* @brief 強連結成分を1つのノードとして扱うグラフを再構築する O(|V|+|E|)
	*/
	void rebuild() {
		rebuildedG.resize(component_count);

		set<pair<ll, ll>> connected;
		rep(v, n) {
			for (auto nv : G[v]) {
				ll v_comp = component[v];
				ll nv_comp = component[nv];
				pair<ll, ll> p = {v_comp, nv_comp};
				if (!is_same(v, nv) &&
					!connected.count(p)) {
					rebuildedG[v_comp].push_back(nv_comp);
					connected.insert(p);
				}
			}
		}
	}

  public:
	/**
	 * @brief 強連結成分分解を行う O(3 * |V|+|E|)
	 * @details 強連結成分を1つのノードとして扱うグラフを再構築する
	 */
	SCC(vector<vector<ll>> &_G) : n(_G.size()), G(_G), rG(vector<vector<ll>>(n)), component(vector<ll>(n, -1)) {
		// 逆辺を張ったグラフを作成
		rep(v, n) {
			for (auto nv : G[v])
				rG[nv].push_back(v);
		}

		topological_sort();
		search_components();
		rebuild();
	}

	//強連結成分の数(新たなグラフのノード数)を取得する
	size_t size() const { return component_count; }
	
	//元の頂点vが属する強連結成分の番号(新たな頂点番号)を取得する 
	ll get_component(ll v) const {
		assert(0 <= v && v < n);
		return component[v];
	}
	//強連結成分のサイズを取得する
	ll get_component_size(ll component) const {
		assert(0 <= component && component < size());
		return components_size[component];
	}
	//強連結成分に属する元の頂点のリストを取得する
	vector<ll> get_component_elements(ll component) const {
		assert(0 <= component && component < size());
		return component_elements[component];
	}

	/**
	 * @brief 新たなグラフのcomponentから伸びている先のリストを取得する
	 * @details あたかもSCCのインスタンスを隣接リストのように扱える
	 * @note トポロジカル順に並んでいる
	 * @attention 戻り値は参照なので破壊的変更に注意
	 * @param component 強連結成分の番号
	 */
	vector<ll>& operator[](ll component) {
		assert(0 <= component && component < size());
		return rebuildedG[component];
	}
	// 暗黙的なvector<vector<ll>>への変換
	operator vvl() const { return rebuildedG; }

	// 元の2頂点が同じ強連結成分に属するかを判定する
	bool is_same(ll u, ll v) { return component[u] == component[v]; }
};

//メイン
int main(){
	ll n,m;
	cin>>n>>m;
	vvl tuv;
	vvl g(n);
	vl ans(n);
	rep(i,m){
		ll t,u,v;
		cin>>t>>u>>v;
		u--,v--;
		g[u].push_back(v);
		tuv.push_back({t,u,v});
	}
	SCC sccs(g);
	rep(i,n)ans[i]=sccs.get_component(i)+1;

	rep(i,m){
		ll u=tuv[i][1];
		ll v=tuv[i][2];
		bool f=false;
		if(tuv[i][0]==0){
			if(ans[u]>ans[v])f=true;
		}else{
			if(ans[u]>=ans[v])f=true;
		}
		if(f){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	vdbg(ans);
	return 0;
}
