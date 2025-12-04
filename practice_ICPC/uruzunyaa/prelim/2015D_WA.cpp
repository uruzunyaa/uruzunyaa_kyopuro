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
#define inf 1e9
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


ll solve(){
	ll n;
	cin>>n;
	if(n==0){return 1;}

	//dp[i][j][k]=i番目のお土産屋まで行ってて、j個の500円玉を獲得済で、k円お釣りをもらわないようにした時。
	//その、使用金額の最小値
	vector<vvl> dp(n+1,vvl(n+1,vl(1000,inf)));

	dp[0][0][0]=0;
	ll kozeni=0,gohyaku=0;

	rep(i,n){
		ll ra;
		cin>>ra;
		ll a=ra%1000;
		if(a==0)a+=1000;


		rep(j,n){
			rep(k,500){
				if(a<=500){
					dp[i+1][j+1][k]=min(dp[i][j][k]+ra,dp[i+1][j+1][k]);
					continue;
				}

				//購入する場合
				
				//500円のお釣りを取れるか判定
				ll nowkozeni=kozeni-k;
				if(nowkozeni<0)nowkozeni+=1000;
				if(a-500<=nowkozeni){
					//お釣りで500円をゲット出来る
					dp[i+1][j+1][k]=min(dp[i][j][k]+ra,dp[i+1][j+1][k]);
				}else{
					//500円を獲得できない
					dp[i+1][j][k]=min(dp[i][j][k]+ra,dp[i+1][j][k]);
				}

				//購入しない場合
				dp[i+1][j][k+(1000-a)]=min(dp[i+1][j][k+(1000-a)],dp[i][j][k]);
			}
		}

		//全てを買う場合をシュミレーション
		if(a<=500){
			gohyaku++;
			kozeni+=1000-a-500;
		}else{
			if(a-500<=kozeni){
				kozeni-=a-500;
				gohyaku++;
			}else{
				kozeni+=1000-a;
			}
		}
	}

	ll ans=inf;
	rep(k,1000){
		ans=min(ans,dp[n][gohyaku][k]);
	}
	cout<<gohyaku<<" "<<ans<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
