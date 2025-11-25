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
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
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
int main(){
	ll n,l,r;
	cin>>n>>l>>r;

	loop(i,l,r){
		if(n%2==i%2){
			ll tmp=n-i;
			tmp/=2;
			ll pluss=tmp+i;
			cout<<"First"<<endl;
			cout<<tmp+1<<" "<<i<<endl;
			
			while(1){
				ll x,y;
				cin>>x>>y;
				if(x==0)break;
				if(x>pluss)x-=pluss;
				else x+=pluss;
				cout<<x<<" "<<y<<endl;
			}
			return 0;
		}
	}
	
	//ここまで来るのはl=rの場合のみ。
	//Grundy数を求める
	vl g(n+1,0);
	loop(i,l,n){
		set<ll> st;
		rep(j,i-l+1){
			//左をj個残す時
			st.insert(g[j]^g[i-l-j]);
		}
		rep(j,inf){
			if(!st.count(j)){
				g[i]=j;
				break;
			}
		}
	}

	map<ll,ll> xy;
	//xy[x]=yは[x,x+y)
	xy[1]=n;
	ll xr=g[n];

	if(g[n]==0){
		cout<<"Second"<<endl;
		ll x,y;
		cin>>x>>y;
		auto it=xy.upper_bound(x);
		it--;

		//この山を消す
		xr^=g[it->second];

		//右側
		if(it->first+it->second!=x+y){
			ll rcnt=(it->first+it->second)-(x+y);
			xy[x+y]=rcnt;
			xr^=g[rcnt];
		}

		//左側
		ll lcnt=x-it->first;
		it->second=lcnt;
		if(it->second==0)xy.erase(it);
		xr^=g[lcnt];

	}else{
		cout<<"First"<<endl;
	}
	
	while(1){
		//xorが0になる場所を探索
		
		ll myx;
		loop(a,1,n-l+1){
			ll x,y;
			x=a,y=l;

			auto it=xy.upper_bound(x);
			
			//有効な操作か確認-1
			if(it==xy.begin()){
				continue;
			}

			it--;

			//有効な操作か確認-2
			if(it->first+it->second<x+y){
				continue;
			}

			//この山を消す
			ll nxr=xr;
			nxr^=g[it->second];

			//右側
			ll rcnt=(it->first+it->second)-(x+y);
			nxr^=g[rcnt];

			//左側
			ll lcnt=x-it->first;
			nxr^=g[lcnt];

			if(nxr==0){
				myx=a;
				break;
			}
		}
		

		//自分の行動の処理
		{
			ll x,y;
			x=myx,y=l;
			cout<<x<<" "<<y<<endl;

			auto it=xy.upper_bound(x);
			it--;

			//この山を消す
			xr^=g[it->second];

			//右側
			if(it->first+it->second!=x+y){
				ll rcnt=(it->first+it->second)-(x+y);
				xy[x+y]=rcnt;
				xr^=g[rcnt];
			}

			//左側
			ll lcnt=x-it->first;
			it->second=lcnt;
			if(it->second==0)xy.erase(it);
			xr^=g[lcnt];
		}

		

		//敵の行動
		{
			ll x,y;
			cin>>x>>y;
			if(x==0)return 0;
			auto it=xy.upper_bound(x);
			it--;

			//この山を消す
			xr^=g[it->second];

			//右側
			if(it->first+it->second!=x+y){
				ll rcnt=(it->first+it->second)-(x+y);
				xy[x+y]=rcnt;
				xr^=g[rcnt];
			}

			//左側
			ll lcnt=x-it->first;
			it->second=lcnt;
			if(it->second==0)xy.erase(it);
			
			xr^=g[lcnt];
		}
		
	}
	return 0;
}
