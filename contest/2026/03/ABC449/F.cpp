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





ll HH,WW,h,w,n;
multiset<ll> st;
ll cnt;
void inserts(ll index){
	st.insert(index);
	auto it=st.lower_bound(index);
	it--;
	ll left=*it;
	it++;
	it++;
	ll right=*it;

	ll before=max(0LL,right-left-w);
	ll now=max(0LL,right-index-w)+max(0LL,index-left-w);

	cnt-=before;
	cnt+=now;
}

void erases(ll index){
	auto it=st.lower_bound(index);
	it--;
	ll left=*it;
	it++;
	it++;
	ll right=*it;
	it--;

	st.erase(it);

	ll now=max(0LL,right-left-w);
	ll before=max(0LL,right-index-w)+max(0LL,index-left-w);

	cnt-=before;
	cnt+=now;
}


//メイン
int main(){
	cin>>HH>>WW>>h>>w>>n;
	priority_queue<vl> pq; 
	rep(i,n){
		//{-高さ,横,0なら削除で1なら追加}
		ll r,c;
		cin>>r>>c;
		pq.push({-r,c,1});
		pq.push({-r-h,c,0});
	}
	pq.push({-inf});
	
	
	st.insert(0);
	st.insert(WW+1);
	
	cnt=WW-w+1;
	while(-pq.top()[0]<=h){
		inserts(pq.top()[1]);
		pq.pop();
	}

	ll mae_takasa=h;
	ll ans=0;
	while(-pq.top()[0]<=HH){
		ll takasa=-pq.top()[0];
		ans+=(takasa-mae_takasa)*cnt;
		while(-pq.top()[0]==takasa){
			if(pq.top()[2]==0){
				erases(pq.top()[1]);
			}else{
				inserts(pq.top()[1]);
			}
			pq.pop();
		}
		mae_takasa=takasa;
	}

	ans+=(HH+1-mae_takasa)*cnt;
	cout<<ans<<endl;
	return 0;
}
