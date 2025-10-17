#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL
#define mod 998244353LL

// Union-Find
struct UnionFind {
	vector<int> par, siz;
	UnionFind(int n) : par(n, -1) , siz(n, 1) { }
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
		return true;
	}
	// x を含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};

//分離可能UnionFind、経路圧縮をしない。
struct CuttingFind{
	vector<int> par, siz;
	CuttingFind(int n) : par(n, -1) , siz(n, 1) { }
	// 根を求める
	int root(int x) {
		if (par[x] == -1) return x;
		else return root(par[x]);
	}
	// x と y が同じグループに属するかどうか (根が一致するかどうか)
	bool issame(int x, int y) {
		return root(x) == root(y);
	}
	//根x と 根y のグループを併合する(お互い根ではない時、falseで何もしない)
	bool unite(int x, int y) {
		if (x == y || par[x] != -1 || par[y] != -1) return false;
		if (siz[x] < siz[y]) swap(x, y);
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}
	//根の側から、その直系の子供を分離する。片方が根でもう片方が直系の子でなければならない。
	bool separate(int x,int y){
		if(par[y]==-1)swap(x,y);
		if(par[y]!=x||par[x]!=-1)return false;
		siz[x] -= siz[y];
		par[y]=-1;
		return true;
	}
	// x を含むグループのサイズを求める
	int size(int x) {
		return siz[root(x)];
	}
};

ll solve(){
	ll n,m;
	cin>>n>>m;
	//if内の条件を書き換える、入力の終わりならreturn 1する。
	if(n==0&&m==0)return 1;

	vvl sab(m,vl(3));

	rep(i,m)cin>>sab[i][1]>>sab[i][2]>>sab[i][0],sab[i][1]--,sab[i][2]--;
	sort(sab.rbegin(),sab.rend());
	CuttingFind cf(n);

	//UnionFind結合をしつつ、いらない辺を削除
	vvl rs;
	rs.push_back({inf,0,0});
	rep(i,m){
		sab[i][1]=cf.root(sab[i][1]);
		sab[i][2]=cf.root(sab[i][2]);
		if(cf.issame(sab[i][1],sab[i][2]))continue;
		cf.unite(sab[i][1],sab[i][2]);
		rs.push_back(sab[i]);
	}

	set<ll> ans;
	rep(i,n)ans.insert(i);

	unordered_set<ll> check;

	//UnionFindをロールバックしながら、最善候補を削る。
	for(ll i=n-1;i>0;i--){
		//その道を消し、調査対象に入れる
		cf.separate(rs[i][1],rs[i][2]);
		check.insert(rs[i][1]);
		check.insert(rs[i][2]);
		
		//もう答えの候補から消えていたらスキップ
		if(!ans.count(cf.root(rs[i][1]))||!ans.count(cf.root(rs[i][2]))){
			ans.erase(rs[i][1]);
			ans.erase(rs[i][2]);
			continue;
		}
		
			

		//この壊れやすさの橋のラスト
		if(rs[i][0]!=rs[i-1][0]){
			ll mx=0;
			//サイズが最も大きい物を見つける
			for(const auto val:check){
				mx=max(mx,(ll)cf.size(val));
			}
			for(const auto val:check){
				if(cf.size(val)!=mx)ans.erase(val),ans.erase(cf.root(val));
			}
			check.clear();
		}
	}
	ll cnt=0;
	for(const auto & val:ans){
		cnt++;
		cout<<val+1;
		if(cnt!=ans.size())cout<<" ";
	}
	cout<<endl;
	return 0;
}

int main(){
	while(1){
		if(solve()==1)break;
	}
	return 0;
}