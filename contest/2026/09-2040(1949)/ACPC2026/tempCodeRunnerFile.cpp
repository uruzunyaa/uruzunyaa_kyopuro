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


struct Node{
	ll to,cost;
};
//Nを頂点数,Mを辺数,Kを指定頂点数として
//計算量(3^K)*N+(2^k)*M log M で
//指定頂点＋自分自身に対する最小全域木のコストを求める
//listは指定頂点のリストを指定する。
vl min_steiner_tree(vector<vector<Node>> &g,vl &list){
	
	ll n=g.size();
	ll k=list.size();

	//dj[i][j]=頂点iのbitjと連結するための最小コスト
	vvl dj(n,vl(1<<k,inf));
	
	//何も含まない物は0で初期化。
	rep(i,n)dj[i][0]=0;
	
	//自分自身が指定頂点である場合も0で初期化。
	rep(i,k)dj[list[i]][1<<i]=0;

	loop(bit,1,(1<<k)-1){
		// {cost,i}で保管
		priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
		rep(i,n){
			//bitの部分列を対象に遷移を行う(3^ndp)
			ll tmp =bit;
			while(1){
				dj[i][bit]=min(dj[i][bit],dj[i][bit-tmp]+dj[i][tmp]);
				if(tmp==0)break;
				tmp = (bit & (tmp-1));
			}
			pq.push({dj[i][bit],i});
		}
		//これでbit0からの遷移だけを考えれば良くなった。
		while(!pq.empty()){
			ll from=pq.top().second;
			ll cost=pq.top().first;
			pq.pop();
			if(dj[from][bit]!=cost)continue;

			//コストでダイクストラ
			rep(i,g[from].size()){
				//更新が起きないならスキップ
				if(dj[g[from][i].to][bit]<=cost+g[from][i].cost)continue;
				dj[g[from][i].to][bit]=cost+g[from][i].cost;
				pq.push({dj[g[from][i].to][bit],g[from][i].to});
			}
		}
	}
	vl ans;
	rep(i,n)ans.push_back(dj[i][(1<<k)-1]);
	return ans;
}


//1次元累積和を生成する。
struct Sums1d{
	ll n;
	vl sums;
	Sums1d(vl row){
		n=(row.size());
		sums=vl(n+1,0);
		rep(i,n){
			sums[i+1]=sums[i]+row[i];
		}
	}
	Sums1d(string row_s){
		n=(row_s.size());
		sums=vl(n+1,0);
		rep(i,n){
			sums[i+1]=sums[i]+row_s[i]-'0';
		}
	}
	//左と右を指定する。(半開区間でない)
	ll get(ll l,ll r){
		if(r<l)return 0;
		r++;
		ll ans=sums[r]-sums[l];
		return ans;
	}
	//末尾にXを追加する。
	void push_back(ll x){
		n++;
		sums.push_back(sums.back()+x);
	}
};



void solve(){
	ll n;
	cin>>n;
	vector<vector<Node>> g(n);
	bool one=true,two=true;
	vl sums;
	rep(i,n-1){
		ll a,b,c;
		cin>>a>>b>>c;
		a--,b--;
		sums.push_back(c);
		g[a].push_back({b,c});
		g[b].push_back({a,c});
		if(a+1!=b)one=false;
	}
	ll q;
	cin>>q;
	vl x(q);
	rep(i,q){
		cin>>x[i];
		x[i]--;
		if(x[i]>=3)two=false;
	}

	if(!one&&!two){
		assert(false);
	}

	if(one){
		Sums1d sm(sums);
		ll mn=inf,mx=-inf;
		rep(i,q){
			mn=min(mn,x[i]);
			mx=max(mx,x[i]);
			if(mn==mx){
				cout<<0<<endl;
				continue;
			}
			//cout<<mn<<" "<<mx<<endl;
			cout<<sm.get(mn,mx-1)<<endl;
		}
	}

	if(two){
		map<ll,vl> anss;
		ll now=0;
		rep(i,q){
			now|=(1LL<<x[i]);
			if(!anss.count(now)){
				vl lists;
				rep(j,3){
					if(now&(1LL<<j))lists.push_back(j);
				}
				anss[now]=min_steiner_tree(g,lists);
			}
			ll ans=inf;
			rep(j,3){
				if(!(now&(1LL<<j)))continue;
				ans=anss[now][j];
			}
			cout<<ans<<endl;
		}
	}
	return;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
