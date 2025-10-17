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

#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード



//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k ,ll mod){
	if(n==0)return 0;
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

//mod mにおけるaの逆元を計算
ll invMod(ll a, ll m) {
	ll b = m, u = 1, v = 0;
	while (b) {
		ll t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	u %= m; 
	if (u < 0) u += m;
	return u;
}

vvl e(100001);
vector<bool> f(100001,true);

ll solve(){
	ll r,c;
	cin>>r>>c;
	if(r==0){return 1;}
	
	if(f[c]==false){
		cout<<"No"<<endl;
		return 0;
	}

	if(c==2){
		cout<<"Yes"<<endl;
		rep(i,r){
			cout<<"0 1"<<endl;
		}
		return 0;
	}

	//素数の時
	if(r%2==0){
		cout<<"No"<<endl;
		return 0;
	}

	vl ans1(c);
	vl ans2(c);
	rep(i,c){
		ans1[i]=i;
		//共通約数で割る
		ll watta=gcd(i,c);
		ans2[i]=(invMod(i/watta,c/watta)*watta);
	}
	vl tmp=ans1;
	rep(j,r/2){
		rep(i,c){
			tmp[i]*=ans1[i];
			tmp[i]*=ans2[i];
			tmp[i]%=c;
		}
	}

	vl invtmp(c);
	rep(i,c)invtmp[tmp[i]]=i;
	
	cout<<"Yes"<<endl;
	rep(j,r/2){
		rep(i,c){
			cout<<ans1[invtmp[i]]<<" ";
		}
		cout<<endl;
		rep(i,c){
			cout<<ans2[invtmp[i]]<<" ";
		}
		cout<<endl;
	}
	rep(i,c){
		cout<<ans1[invtmp[i]]<<" ";
	}
	cout<<endl;

	return 0;
}

//メイン
int main(){
	loop(i,2,100000){
		if(e[i].size()==0){
			for(ll j=1;i*j<=100000;j++){
				if(j%i==0){
					f[j*i]=false;
				}
				e[j*i].push_back(i);
			}
		}
	}
	while(solve()==0);
	return 0;
}
