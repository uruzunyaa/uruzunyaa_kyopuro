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

//#include<boost/multiprecision/cpp_int.hpp>
//#define bbi boost::multiprecision::cpp_int
//#include<atcoder/lazysegtree>


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	n%=mod;
	ll ans = 1;
	while (k > 0){
		if ((k&1) ==1)ans=(ans*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return ans;
}

//受け取った2次元文字の外側に、文字pをコーティングする。
vector<string> pad(vector<string> &s,char p){
	ll h=s.size();
	ll w=s[0].size();
	vector<string> res(h+2,string(w+2,p));
	rep(i,h)rep(j,w)res[i+1][j+1]=s[i][j];
	return res;
}

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


//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};


//メイン
//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

vl dfs(ll node,ll mae,vvl &g,vl & a){
	//{自分を選ぶ、自分を選ばず親を強制選び、自分を選ばず親自由};
	vl ans(3,0);

	vvl list;
	for(auto val:g[node]){
		if(val==mae)continue;
		list.push_back(dfs(val,node,g,a));
	}
	
	//自分を選ぶ
	ans[0]+=a[node];
	ll cnt=0;
	vl cost;
	rep(i,list.size()){
		ans[0]+=min(list[i][0],min(list[i][1],list[i][2]));
		ans[1]+=min(list[i][0],list[i][2]);
		ans[2]+=min(list[i][0],list[i][2]);
		if(list[i][0]<=list[i][2]){
			cnt++;
		}else{
			cost.push_back(list[i][0]-list[i][2]);
		}
	}
	sort(cost.rbegin(),cost.rend());
	if(cnt+cost.size()<1){
		ans[1]=inf;
		ans[2]=inf;
		return ans;
	}
	if(cnt==0){
		ans[1]+=cost.back();
		ans[2]+=cost.back();
		cost.pop_back();
		cnt++;
	}
	if(cnt+cost.size()<2){
		ans[2]=inf;
		return ans;
	}
	if(cnt==1){
		ans[2]+=cost.back();
		cost.pop_back();
		cnt++;
	}
	return ans;
}

int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];

	vvl g(n);
	rep(i,n-1){
		ll u,v;
		cin>>u>>v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vl ans=dfs(0,-1,g,a);
	cout<<min(ans[0],ans[2])<<endl;
	return 0;
}
