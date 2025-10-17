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

void solve(){
	ll x,y;
	cin>>x>>y;
	vl a(7,0);
	ll a12,a21;
	cin>>a[1]>>a12>>a21>>a[2];

	ll sumax=a[1]+a[2]*2+a12+a21*2;
	ll sumay=a[1]+a[2]*2+a12*2+a21;

	ll mx=min(sumax/x,sumay/y);
	ll mn=0;
	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;
		bool f=true;

		vl b=a;
		ll nxy;
		if(x<=y){
			b[3]=min(a21,a12-(y-x)*mid);
			nxy = x - (y-x);
		}else{
			b[3]=min(a12,a21-(x-y)*mid);
			nxy = y - (x-y);
		}
		if(nxy<0){
			cout<<0<<endl;
			return;
		}
		if(b[3]<0){
			f=false;
		}else{
			//b1,b2,b3の和で、nxをmid個作れるか
			if(nxy<2)b[2]=0;
			if(nxy<3)b[3]=0;

			//6の塊の必要数
			ll cntsix = mid * (nxy/6);
			
			if(nxy%6==1){
				//{3,2,2},{1}
				ll herasu = min(mid,min(b[2]/2,b[3]));
				cntsix-=herasu;
				b[2]-=herasu*2;
				b[3]-=herasu;
				ll nokori = mid-herasu;

				b[1] -= nokori;
				if(b[1]<0) f=false;
			}
			if(nxy%6==2){
				//{2},{1,1}
				ll herasu = min(mid,b[2]);
				b[2] -= herasu;
				ll nokori = mid-herasu;

				b[1] -= nokori*2;
				if(b[1]<0) f=false;
			}
			if(nxy%6==3){
				//{3},{2,1},{1,1,1}
				ll herasu = min(mid,b[3]);
				b[3] -= herasu;
				ll nokori = mid-herasu;
				
				ll herasu2 = min(min(nokori,b[2]),b[1]);
				b[2] -= herasu2;
				b[1] -= herasu2;
				nokori -= herasu2;

				b[1] -= nokori*3;
				if(b[1]<0) f=false;
			}
			if(nxy%6==4){
				//{2,2},{3,1},{2,1,1},{1,1,1,1}
				ll herasu = min(mid,b[2]/2);
				b[2] -= herasu*2;
				ll nokori = mid-herasu;
				
				ll herasu2 = min(min(nokori,b[3]),b[1]);
				b[3] -= herasu2;
				b[1] -= herasu2;
				nokori -= herasu2;
				
				ll herasu3 = min(nokori,min(b[2],b[1]/2));
				b[1] -= herasu3*2;
				b[2] -= herasu3;
				nokori -= herasu3;

				b[1]-=nokori*4;
				if(b[1]<0) f=false;
			}
			if(nxy%6==5){
				//{3,2},{3,1,1},{2,2,1},{2,1,1,1},{1,1,1,1,1}
				ll herasu = min(mid,min(b[2],b[3]));
				b[3] -= herasu;
				b[2] -= herasu;
				ll nokori = mid-herasu;
				
				ll herasu2 = min(nokori,min(b[3],b[1]/2));
				b[3] -= herasu2;
				b[1] -= herasu2*2;
				nokori -= herasu2;
				
				ll herasu3 = min(nokori,min(b[2]/2,b[1]));
				b[1] -= herasu3;
				b[2] -= herasu3*2;
				nokori -= herasu3;

				ll herasu4 = min(nokori,min(b[2],b[1]/3));
				b[1] -= herasu4*3;
				b[2] -= herasu4;
				nokori -= herasu4;

				b[1]-=nokori*5;
				if(b[1]<0) f=false;
			}
			
			//2を出来る限り6に
			cntsix-= b[2]/3;
			b[2]%=3;
			
			//2の余りを出来る限り1と組み合わせて3へ
			ll cnt12 = min(b[1],b[2]);
			b[3]+=cnt12;
			b[1]-=cnt12;

			//1を出来る限り3へ
			b[3]+=b[1]/3;

			//3を全て6へ
			cntsix-= b[3]/2;
			
			if(cntsix>0)f=false;
		}

		if(f)mn=mid;
		else mx=mid-1;
	}
	cout<<mn<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
