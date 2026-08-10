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

void solve(){
	return;
}



//メイン
int main(){
	ll q;
	cin>>q;
	vector<deque<ll>> now(6);
	rep(z,q*2){
		ll t;
		cin>>t;
		if(t==1){
			vvl sousa;
			
			ll mx;
			if(now[4].size()+now[3].size()+now[2].size()+now[1].size()>729)mx=5;
			else if(now[3].size()+now[2].size()+now[1].size()>81)mx=4;
			else if(now[2].size()+now[1].size()>9)mx=3;
			else mx=2;

			vector<pair<ll,ll>> junjo;
			loop(i,1,mx){
				rep(j,now[i].size())junjo.push_back({now[i][j],i});
			}
			sort(junjo.begin(),junjo.end());
			rep(i,junjo.size())sousa.push_back({junjo[i].second,mx});

			ll x;
			cin>>x;			
			now[1].push_back(x);
			cout<<sousa.size()<<endl;
			rep(i,sousa.size()){
				ll tmp=now[sousa[i][0]].front();
				now[sousa[i][0]].pop_front();
				now[sousa[i][1]].push_back(tmp);
				cout<<sousa[i][0]<<" "<<sousa[i][1]<<endl;
			}
		}else{
			ll ans=1;
			loop(i,1,5){
				if(now[i].empty())continue;
				if(now[ans][0]>now[i][0])ans=i;
			}
			now[ans].pop_front();
			cout<<ans<<endl;
		}
	}

}
