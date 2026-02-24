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
	ll n,q;
	string s;
	cin>>n>>s>>q;

	ll ans=0;
	rep(i,n-1){
		if(s[i]!=s[i+1]||s[i]=='?')ans++;
	}

	vl a(3,0),b(3,0),c(3,0);
	ll aa=0,bb=0,cc=0;

	ll cnt=0;
	char mae='A';
	loop(i,1,n-1){
		if(s[i]=='?')cnt++;
		else{
			if(cnt!=0){
				//A
				{
					ll zero=cnt+1;
					if(mae=='A')zero--;
					if(s[i]=='A')zero--;
					ll one=zero%2;
					zero/=2;
					ll two=cnt-zero-one;

					a[0]+=zero;
					a[1]+=one;
					a[2]+=two;
				}

				//B
				{
					ll zero=cnt+1;
					if(mae=='B')zero--;
					if(s[i]=='B')zero--;
					ll one=zero%2;
					zero/=2;
					ll two=cnt-zero-one;

					b[0]+=zero;
					b[1]+=one;
					b[2]+=two;
				}

				//C
				{
					ll zero=cnt+1;
					if(mae=='C')zero--;
					if(s[i]=='C')zero--;
					ll one=zero%2;
					zero/=2;
					ll two=cnt-zero-one;

					c[0]+=zero;
					c[1]+=one;
					c[2]+=two;
				}
				//aa,bb,ccの囲い
				{
					if(mae==s[i]&&cnt%2==1){
						if(mae=='A')aa++;
						if(mae=='B')bb++;
						if(mae=='C')cc++;
					}
				}
			}
			
			mae=s[i];
			cnt=0;
		}
	}

	vl ma={0},mb={0},mc={0};
	rep(i,3){
		rep(j,a[i])ma.push_back(ma.back()+i);
		rep(j,b[i])mb.push_back(mb.back()+i);
		rep(j,c[i])mc.push_back(mc.back()+i);
	}

	while(q--){
		ll x,y,z;
		cin>>x>>y>>z;
		ll kotae=ans-ma[x]-mb[y]-mc[z];

		//aa
		{
			ll yoryoku=max(0LL,b[0]-y)+max(0LL,c[0]-z);
			kotae-=max(0LL,aa-yoryoku);
		}
		//bb
		{
			ll yoryoku=max(0LL,a[0]-x)+max(0LL,c[0]-z);
			kotae-=max(0LL,bb-yoryoku);
		}
		//cc
		{
			ll yoryoku=max(0LL,b[0]-y)+max(0LL,a[0]-x);
			kotae-=max(0LL,cc-yoryoku);
		}
		cout<<kotae<<endl;
	}
	return 0;
}
