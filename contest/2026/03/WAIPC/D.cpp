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
	ll n,m;
	cin>>n>>m;
	vl a(m),b(m);
	rep(i,m)cin>>a[i]>>b[i],a[i]--,b[i]--;

	//0判定
	{
		if(m==0){
			cout<<0<<endl;
			return;
		}
		if(m==1){
			if(a[0]==0&&b[0]==1){
				cout<<0<<endl;
				return;
			}
		}
	}


	//1で可能か判定
	{
		bool f=true;
		vl func(n,-1);
		vl in(n,0);
		func[0]=1;
		rep(i,m){
			if(a[i]==0&&b[i]==1)continue;
			if(func[a[i]]!=-1||in[b[i]]!=0){
				f=false;
				break;
			}
			func[a[i]]=b[i];
			in[b[i]]=1;
		}
		if(f){
			vl ans;
			stack<ll> ok;
			rep(i,n){
				if(in[i]==0)ok.push(i);
			}
			if(ok.size()==0){
				//全体がサイクル成分なので1ヵ所スタート
				ok.push(0);
				in[0]=-inf;
			}
			while(!ok.empty()){
				ll tmp=ok.top();
				ans.push_back(tmp);
				ok.pop();
				if(func[tmp]==-1)continue;
				in[func[tmp]]--;
				if(in[func[tmp]]==0)ok.push(func[tmp]);
			}
			if(ans.size()==n){
				rep(i,n)ans[i]++;
				cout<<1<<endl;
				vdbg(ans);
				return;
			}
		}
	}

	//2判定
	{
		if(n%2==0){
			cout<<2<<endl;
			rep(i,n/2){
				cout<<i+1<<" ";
				cout<<n-i<<" ";	
			}
			cout<<endl;
			rep(i,n)cout<<i+1<<" ";
			cout<<endl;
			return;
		}
		if(n!=3){
			cout<<2<<endl;
			rep(i,n/2){
				cout<<i+1<<" ";
				cout<<n-i<<" ";	
			}
			cout<<(n+1)/2<<endl;
			rep(i,n/2){
				cout<<i+1<<" ";
				cout<<(n/2)+i+2<<" ";	
			}
			cout<<(n+1)/2<<endl;
			return;
		}
	}
	cout<<-1<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
