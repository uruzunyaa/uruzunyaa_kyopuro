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


bool isinner(vl l,vl r,vl x){
	rep(i,x.size()){
		if((x[i]<l[i]&&x[i]<r[i])||(x[i]>l[i]&&x[i]>r[i])){
			return false;
		}
	}
	return true;
}

//メイン
int main(){
	ll h,w,k;
	cin>>h>>w>>k;

	vector<string> s(h);
	rep(i,h)cin>>s[i];

	vvl m;

	ll anscheck=0;

	rep(i,h){
		rep(j,w){
			if(s[i][j]=='#')m.push_back({i,j,1});
			if(s[i][j]=='P'){
				anscheck+=(1LL<<m.size());
				m.push_back({i,j,2});
			}
		}
	}

	vector<vvl> dist(h,vvl(w,vl(1<<m.size(),inf)));

	dist[0][0][0]=0;

	queue<vl> bfs;
	bfs.push({0,0,0});

	ll ans=inf;

	while(!bfs.empty()){
		ll x=bfs.front()[0];
		ll y=bfs.front()[1];
		ll bit=bfs.front()[2];
		bfs.pop();

		if((bit&anscheck)==anscheck)ans=min(ans,dist[x][y][bit]);

		//上下左右への移動
		rep(i,4){
			ll nx=x+dx[i];
			ll ny=y+dy[i];
			if(nx<0||nx>=h||ny<0||ny>=w)continue;
			ll nbit=bit;
			bool f=false;
			rep(j,m.size()){
				if(((1LL<<j)&bit)==0&&m[j][0]==nx&&m[j][1]==ny){
					if(m[j][2]==1){
						f=true;
						break;
					}else{
						nbit+=1LL<<j;
					}
				}
			}
			if(f)continue;
			if(dist[nx][ny][nbit]!=inf)continue;
			bfs.push({nx,ny,nbit});
			dist[nx][ny][nbit]=dist[x][y][bit]+1;
		}

		//上下左右へのブレス
		rep(i,4){
			ll nbit=bit;
			bool f=false;
			rep(j,m.size()){
				if(((1LL<<j)&bit)==0&&isinner({x,y},{x+dx[i]*k,y+dy[i]*k},{m[j][0],m[j][1]})){
					if(m[j][2]==2){
						f=true;
						break;
					}else{
						nbit+=1LL<<j;
					}
				}
			}
			if(f)continue;
			if(dist[x][y][nbit]!=inf)continue;
			bfs.push({x,y,nbit});
			dist[x][y][nbit]=dist[x][y][bit]+1;
		}
	}
	if(ans==inf)cout<<-1<<endl;
	else cout<<ans<<endl;
	return 0;
}
