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

void solve(){
	ll n;
	cin>>n;
	vl y(n);
	set<ll> st;
	rep(i,n)cin>>y[i],y[i]--,st.insert(y[i]);

	if(st.size()!=n){
		cout<<"No"<<endl;
		return;
	}

	ll cnt=0;
	
	rep(i,n){
		if(y[i]==i)cnt++;
		if(y[y[i]]!=i){
			cout<<"No"<<endl;
			return ;
		}
	}

	if(n%2==1&&cnt!=1){
		cout<<"No"<<endl;
		return ;
	}

	//round-robin
	ll m=n;
	if(n%2==0)m--;
	vvl a(n,vl(n,n));
	loop(i,1,m){
		rep(j,m){
			ll tmp=(2*m-i-j)%m;
			if(j==tmp&&n%2==0){
				a[j][n-1]=i;
				a[n-1][j]=i;
			}else{
				a[j][tmp]=i;
			}
		}
	}


	set<pair<ll,ll>> diff;
	set<ll> same;
	rep(i,n)rep(j,n){
		if(a[i][j]==1){
			if(i==j)same.insert(i);
			else diff.insert({i,j});
		}
	}

	cnt/=2;
	while(cnt--){
		pair<ll,ll> tmp=*diff.begin();
		ll i=tmp.first,j=tmp.second;
		diff.erase(diff.begin());
		diff.erase({j,i});
		swap(a[i][i],a[i][j]);
		swap(a[j][j],a[j][i]);
		same.insert(i);
		same.insert(j);
	}

	

	vl p(n,inf);
	rep(i,n){
		if(p[i]!=inf)continue;
		if(y[i]==i){
			p[i]=*same.begin();
			same.erase(same.begin());
		}else{
			ll j=y[i];
			pair<ll,ll> tmp=*diff.begin();
			p[i]=tmp.first;
			p[j]=tmp.second;
			diff.erase({tmp.second,tmp.first});
			diff.erase({tmp.first,tmp.second});
		}
	}
	cout<<"Yes"<<endl;
	rep(i,n){
		rep(j,n){
			cout<<a[p[i]][p[j]]<<" ";
		}
		cout<<endl;
	}
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
