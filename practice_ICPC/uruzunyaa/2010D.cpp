//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vector<ll>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 1e9
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

struct node{
	ll cnt,ysum;
};

ll solve(){
	ll w,h;
	cin>>w>>h;
	if(w==0){return 1;}
	
	vector<string> s(h);
	rep(i,h)cin>>s[i];

	vector<node> nd;
	vvl f(h,vl(w,inf));
	ll num=0;
	
	rep(i,h){
		rep(j,w){
			if(f[i][j]!=inf)continue;
			if(s[i][j]=='.')continue;
			nd.push_back({0,0});
			queue<pair<ll,ll>> qp;
			qp.push({i,j});
			while(!qp.empty()){
				ll x=qp.front().first;
				ll y=qp.front().second;
				qp.pop();
				if(f[x][y]!=inf)continue;
				
				f[x][y]=num;
				nd[num].cnt++;
				nd[num].ysum+=y;

				rep(k,4){
					ll nx=x+dx[k];
					ll ny=y+dy[k];
					if(nx<0||nx==h||ny<0||ny==w)continue;
					if(s[i][j]!=s[nx][ny])continue;
					qp.push({nx,ny});
				}
			}
			num++;
		}
	}
	vector<set<ll>> g(num);
	vl distmn(num,inf);
	vl distmx(num,-inf);
	vl cnt(num,0);
	rep(i,h-1){
		rep(j,w){
			if(f[i][j]==f[i+1][j])continue;
			if(f[i][j]==inf)continue;
			if(f[i+1][j]==inf)continue;
			distmn[f[i][j]]=min(distmn[f[i][j]],j);
			distmx[f[i][j]]=max(distmx[f[i][j]],j);
			if(g[f[i][j]].count(f[i+1][j]))continue;
			g[f[i][j]].insert(f[i+1][j]);
			cnt[f[i+1][j]]++;
		}
	}
	rep(j,w){
		if(f[h-1][j]==inf)continue;
		distmn[f[h-1][j]]=min(distmn[f[h-1][j]],j);
		distmx[f[h-1][j]]=max(distmx[f[h-1][j]],j);
	}

	queue<ll> qu;
	rep(i,num)if(cnt[i]==0)qu.push(i);

	//vvdbg(f);
	// vdbg(distmn);
	// vdbg(distmx);


	rep(i,num){
		ll tmp=qu.front();
		qu.pop();
		//今のコイツの重心を求めて、行き先の奴の上か判定
		if(nd[tmp].cnt * (2*distmn[tmp]-1)>= nd[tmp].ysum * 2){
			cout<<"UNSTABLE\n";
			return 0;
		}

		if(nd[tmp].cnt * (2*distmx[tmp]+1)<= nd[tmp].ysum * 2){
			cout<<"UNSTABLE\n";
			return 0;
		}

		//今のコイツの重心情報を行き先の奴に加算
		ll next=*g[tmp].begin();
		nd[next].cnt+=nd[tmp].cnt;
		nd[next].ysum+=nd[tmp].ysum;

		//行き先の奴の上の処理が全て終わってたらquに突っ込む
		cnt[next]--;
		if(cnt[next]==0)qu.push(next);
	}
	cout<<"STABLE"<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
