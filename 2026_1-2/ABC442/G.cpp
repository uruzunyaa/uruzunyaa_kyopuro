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

//aの方が小さいか判定
bool ck(vl a,vl b){
	ll aa=b[0]*a[1];
	ll bb=a[0]*b[1];
	return aa<bb;
}

//メイン
int main(){
	ll n,c;
	cin>>n>>c;
	vvl wvk;
	rep(i,n){
		ll w,v,k;
		cin>>w>>v>>k;
		wvk.push_back({w,v,k});
	}
	sort(wvk.begin(),wvk.end(),ck);

	vector<queue<ll>> qq(4);

	ll ans=0;
	rrep(i,n){
		if(wvk[i][0]*wvk[i][2]<=c){
			ans+=wvk[i][1]*wvk[i][2];
			c-=wvk[i][0]*wvk[i][2];
			rep(j,min(2LL,wvk[i][2]))qq[wvk[i][0]].push(wvk[i][1]);
			wvk.pop_back();
			continue;
		}
		ll cnt=c/wvk[i][0];
		c%=wvk[i][0];
		wvk[i][2]-=cnt;
		ans+=wvk[i][1]*cnt;
		rep(j,min(2LL,cnt))qq[wvk[i][0]].push(wvk[i][1]);
		break;
	}
	if(c>3){
		cout<<ans<<endl;
		return 0;
	}

	loop(i,1,3){
		while(qq[i].size()>0){
			if(qq[i].size()<=2){
				wvk.push_back({i,qq[i].front(),1});
				ans-=qq[i].front();
				c+=i;
			}
			qq[i].pop();
		}
	}
	vl dp(c+1,-inf);
	dp[0]=ans;

	rep(i,wvk.size()){
		rep(z,min(12LL,wvk[i][2])){
			vl ndp=dp;
			loop(j,0,c-wvk[i][0]){
				ndp[j+wvk[i][0]]=max(ndp[j+wvk[i][0]],dp[j]+wvk[i][1]);
			}
			swap(dp,ndp);
		}
	}

	rep(i,c+1){
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
	return 0;
}
