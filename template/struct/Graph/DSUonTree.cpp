//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
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

template <typename G>
struct DSUonTree{
private:
	G &g;
	int N;
	vector<int> sub_sz, euler, down, up;
	int idx_;
	int root;

	//heavy childeを0に持ってくる
	int dfs1(int cur, int par = -1){
		sub_sz[cur] = 1;
		//無向グラフの際に使えるよう、親がheavyにならないよう対策
		if ((int)g[cur].size() >= 2 and g[cur][0] == par){
			swap(g[cur][0], g[cur][1]);
		}
		for (auto &dst : g[cur]){
			if (dst == par)continue;
			sub_sz[cur] += dfs1(dst, cur);
			if (sub_sz[dst] > sub_sz[g[cur][0]])swap(dst, g[cur][0]);
		}
		return sub_sz[cur];
	}
	//オイラーツアーを作る
	void dfs2(int cur, int par = -1){
		euler[idx_] = cur;
		down[cur] = idx_++;
		for (auto &dst : g[cur]){
			if (dst == par)continue;
			dfs2(dst, cur);
		}
		up[cur] = idx_;
	}

public:
	DSUonTree(G &_g, int _root = 0):
	g(_g),
	N(_g.size()),
	sub_sz(_g.size()),
	euler(_g.size()),
	down(_g.size()),
	up(_g.size()),
	idx_(0),
	root(_root){
		dfs1(root);
		dfs2(root);
	}

	//オイラーツアーのindexを取得出来る
	int idx(int u) const { return down[u]; }

	template <typename UPDATE, typename QUERY, typename CLEAR, typename RESET>
	void run(UPDATE &add, QUERY &query, CLEAR &erase, RESET &reset){
		auto dsu = [&](auto rc, int cur, int par = -1, bool keep = false) -> void{
			//軽い子を処理して消す
			for (int i = 1; i < (int)g[cur].size(); i++)if (g[cur][i] != par)rc(rc, g[cur][i], cur, false);
			//葉じゃなければ重い子を処理して残す
			if (sub_sz[cur] != 1)rc(rc, g[cur][0], cur, true);
			//軽い子を全て追加し直す(答えの処理は終わってるので非再帰)
			if (sub_sz[cur] != 1)for (int i = up[g[cur][0]]; i < up[cur]; i++)add(euler[i]);
			//自分自身を追加
			add(cur);
			//クエリを処理(答えを保存)
			query(cur);
			//消したい場合、非再帰で痕跡を残さず削除
			if (!keep){
				for (int i = down[cur]; i < up[cur]; i++)erase(euler[i]);
				reset();
			}
			return;
		};
		dsu(dsu, root);
	}
};

// メイン
int main(){
	//グラフを入れる(無向でも良い)
	vvl g;

	// 頂点iの情報を追加する
	auto add = [&](int i) {
		
	};

	// 頂点iを根とする部分木について、答えの保存をする
	auto query = [&](int i) {
		
	};

	// 頂点 i の情報を、現在持っているデータ構造から削除する
	auto erase = [&](int i) {
		
	};

	// データ構造全体を初期状態に戻す(最大値等のリセット,個別の頂点情報の削除は含まない)
	auto reset = [&]() {

	};

	//DSU on Tree実行、引数はグラフと根
	DSUonTree<decltype(g)> dot(g, 0);
	dot.run(add, query, erase, reset);
	
	return 0;
}
