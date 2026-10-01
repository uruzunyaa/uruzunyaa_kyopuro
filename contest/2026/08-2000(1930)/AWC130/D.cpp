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


// Union-Find
struct UnionFind {
	vector<int> par, siz;
	vvl udlr;
	UnionFind(int n) : par(n, -1) , siz(n, 1) {
		udlr=vvl(n,vl(4));
	}
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
		udlr[x][0]=min(udlr[y][0],udlr[x][0]);
		udlr[x][1]=max(udlr[y][1],udlr[x][1]);
		udlr[x][2]=min(udlr[y][2],udlr[x][2]);
		udlr[x][3]=max(udlr[y][3],udlr[x][3]);
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

//imos法。サイズ与えたら0初期化、配列ならそれで初期化
//加算は閉区間[l,r]で行われる。
struct Imos2d{
	ll h,w;
	vvl sums;
	Imos2d(ll height,ll width){
		h=height;
		w=width;
		sums=vvl(h+1,(vl(w+1,0)));
	}
	Imos2d(vvl a){
		h=a.size();
		w=a[0].size();
		sums=vvl(h+1,(vl(w+1,0)));
		rep(i,h)rep(j,w){
			sums[i][j]+=a[i][j];
			sums[i+1][j+1]+=a[i][j];
			sums[i][j+1]-=a[i][j];
			sums[i+1][j]-=a[i][j];
		}
	}
	//[l,r]にxを加算
	void add(ll u,ll d,ll l,ll r,ll x){
		if(d<u)return;
		if(r<l)return;
		d++;
		r++;
		
		sums[u][l]+=x;
		sums[d][r]+=x;
		sums[u][r]-=x;
		sums[d][l]-=x;
	}
	//現時点を復元して返す。
	vvl get(){
		vvl ans(h,vl(w));
		rep(i,h)rep(j,w){
			ans[i][j]=sums[i][j];
			if(i!=0)ans[i][j]+=ans[i-1][j];
			if(j!=0)ans[i][j]+=ans[i][j-1];
			if(i!=0&&j!=0)ans[i][j]-=ans[i-1][j-1];
		}
		return ans;
	}
};


//二次元累積和を生成する。
struct Sums2d{
	ll h,w;
	vvl sums;
	Sums2d(vvl row){
		h=(row.size());
		w=(row[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row[i][j];
		}
	}
	Sums2d(vector<string> row_s){
		h=(row_s.size());
		w=(row_s[0].size());
		sums=vvl(h+1,vl(w+1,0));
		rep(i,h)rep(j,w){
			sums[i+1][j+1]+=sums[i+1][j];
			sums[i+1][j+1]+=sums[i][j+1];
			sums[i+1][j+1]-=sums[i][j];
			sums[i+1][j+1]+=row_s[i][j]-'0';
		}
	}
	//左上座標と右下座標を指定する。(半開区間でない)
	ll get(ll u,ll l,ll d,ll r){
		if(d<u||r<l)return 0;
		d++,r++;
		ll ans=0;
		ans+=sums[u][l];
		ans+=sums[d][r];
		ans-=sums[u][r];
		ans-=sums[d][l];
		return ans;
	}
};
//メイン
int main(){
	ll h,w,n;
	cin>>h>>w>>n;

	Imos2d im(h,w);

	rep(i,n){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		a--,b--,c--,d--;
		im.add(a,b,c,d,1);
	}

	vvl data=im.get();
	rep(i,h)rep(j,w)data[i][j]%=2;

	Sums2d sums(data);
	vvl sima;

	UnionFind uf(h*w);
	rep(i,h)rep(j,w)uf.udlr[i*w+j]={i,i,j,j};
	rep(i,h-1)rep(j,w){
		if(data[i][j]==1&&data[i+1][j]==1)uf.unite(i*w+j,(i+1)*w+j);
	}
	rep(i,h)rep(j,w-1){
		if(data[i][j]==1&&data[i][j+1]==1)uf.unite(i*w+j,i*w+j+1);
	}
	rep(i,h)rep(j,w){
		if(data[i][j]==0)continue;
		if(uf.root(i*w+j)!=i*w+j)continue;
		sima.push_back(uf.udlr[i*w+j]);
	}

	ll m;
	cin>>m;
	rep(i,m){
		ll a,b,c,d;
		cin>>a>>b>>c>>d;
		a--,b--,c--,d--;
		ll cnt=0;
		rep(j,sima.size()){
			if(sima[j][0]>=a&&sima[j][1]<=b&&sima[j][2]>=c&&sima[j][3]<=d)cnt++;
		}
		cout<<sums.get(a,c,b,d)<<" "<<cnt<<endl;
	}

	return 0;
}
