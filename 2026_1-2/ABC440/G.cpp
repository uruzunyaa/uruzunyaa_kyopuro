//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
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

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

ll f,h,w;
ll ind(ll k,ll i,ll j){
	return k*h*w+i*w+j;
}

vvl G,revG;
vl cost;

vector<vector<pair<ll,ll>>> zmx,omx;
//zmx[i]=頂点iより先、ハシゴを追加しない時、{スコア,行く頂点}
//omx[i]=頂点iより先、ハシゴを追加した時、{スコア,ハシゴを掛けた頂点}

ll zerodfs(ll node){
	if(zmx[node].size()!=0)return zmx[node][0].first;
	zmx[node].push_back({cost[node],-1});
	rep(i,G[node].size()){
		zmx[node].push_back({zerodfs(G[node][i])+cost[node],G[node][i]});
	}
	sort(zmx[node].rbegin(),zmx[node].rend());
	while(zmx[node].size()>2)zmx[node].pop_back();
	return zmx[node][0].first;
}

vector<pair<ll,ll>> onedfs(ll node){
	if(omx[node].size()!=0)return omx[node];
	omx[node].push_back({cost[node],-1});
	
	//今ハシゴを置く場合
	for(auto val:revG[node]){
		//自分に戻って来る場合
		pair<ll,ll> tmp={cost[val]+zmx[node][0].first,val};

		//戻ってこない場合
		ll f_or_s;
		if(zmx[val][0].second!=node)f_or_s=0;
		else f_or_s=1;
		
		tmp=max(tmp,{cost[node]+zmx[val][f_or_s].first,val});
		omx[node].push_back(tmp);
	}

	//まだハシゴを置かない場合
	for(auto val:G[node]){
		auto tmp=onedfs(val);
		
		ll f_or_s;
		if(tmp[0].second!=node)f_or_s=0;
		else f_or_s=1;
	
		omx[node].push_back({cost[node]+tmp[f_or_s].first,-1});
	}
	
	sort(omx[node].rbegin(),omx[node].rend());
	while(omx[node].size()>2)omx[node].pop_back();
	return omx[node];
}

//メイン
int main(){
	cin>>f>>h>>w;
	vector<vector<string>> s(f,vector<string>(h));
	rep(i,f)rep(j,h)cin>>s[i][j];
	
	vvl g(f*h*w);
	rep(k,f)rep(i,h)rep(j,w){
		if(s[k][i][j]=='#')continue;
		//横と縦
		rep(d,4){
			ll ni=i+dx[d];
			ll nj=j+dy[d];
			if(ni<0||ni>=h||nj<0||nj>=w)continue;
			if(s[k][ni][nj]=='#')continue;
			g[ind(k,i,j)].push_back(ind(k,ni,nj));
		}
		if(k==f-1)continue;
		if(s[k+1][i][j]=='#')continue;
		g[ind(k,i,j)].push_back(ind(k+1,i,j));
	}
	SCC G_scc(g);
	G=G_scc;
	ll n=G.size();

	revG=vvl(n);
	rep(i,n){
		rep(j,G[i].size()){
			revG[G[i][j]].push_back(i);
		}
	}

	cost=vl(n,0);
	zmx=vector<vector<pair<ll,ll>>>(n);
	omx=vector<vector<pair<ll,ll>>>(n);
	rep(i,n){
		vl list=G_scc.get_component_elements(i);
		for(auto val:list){
			ll x=val/(h*w);
			ll y=(val%(h*w))/w;
			ll z=val%w;
			cost[i]+=s[x][y][z]-'0';
		}
	}
	rep(i,n)zerodfs(i);
	rep(i,n)onedfs(i);

	ll q;
	cin>>q;
	while(q--){
		ll z,x,y;
		cin>>z>>x>>y;
		z--,x--,y--;

		ll node=G_scc.get_component(ind(z,x,y));
		cout<<max(onedfs(node)[0].first,zerodfs(node))<<endl;
	}
	return 0;
}
