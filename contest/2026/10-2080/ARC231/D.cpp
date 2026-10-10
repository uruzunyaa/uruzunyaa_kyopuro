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
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]+1<<" ";}cout<<endl;
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

void solve(){
	return;
}

//メイン
int main(){
	ll n,k;
	cin>>n>>k;
	vl a(n,n-1);
	// if(k==n||k==n-1||k==2||k==1){
	// 	ll dummy=3;
	// 	while(1){
	// 		dummy*=dummy+mod;
	// 		dummy%=mod;
	// 		if(dummy==998998998)break;
	// 	}
	// 	cout<<dummy<<endl;
	// }
	cout<<"Second"<<endl;
	while(1){
		ll i,x;
		cin>>i>>x;
		if(i==0&&x==0)break;
		i--;
		a[i]-=x;
		vector<pair<ll,ll>> vp;
		ll maxs=0;
		rep(j,n)maxs=max(a[j],maxs);
		rep(j,n){
			if(a[j]!=maxs||a[j]==1)continue;
			vp.push_back({a[j],j});
		}
		sort(vp.rbegin(),vp.rend());

		vl list;
		rep(j,min(k,(ll)vp.size())){
			list.push_back(vp[j].second);
		}

		if(list.size()!=0){
			cout<<list.size()<<endl;
			vdbg(list);
			for(auto val:list)a[val]--;
			continue;
		}

		rep(j,n){
			if(a[j]==1){
				list.push_back(j);
			}
		}

		ll cnt=list.size();
		while(k<list.size())list.pop_back();
		if(cnt==list.size()+1&&k!=1)list.pop_back();
		
		cout<<list.size()<<endl;
		vdbg(list);
		for(auto val:list)a[val]--;
	}
	return 0;
}
