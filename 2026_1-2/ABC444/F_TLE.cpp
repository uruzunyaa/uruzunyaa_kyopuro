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
	ll mxsum=0;
	vl a(n);
	rep(i,n)cin>>a[i],mxsum+=a[i];
	mxsum-=(m+n)/2;

	sort(a.rbegin(),a.rend());
	

	//答えとなる中央値でにぶたん
	ll mn=1,mx=1000000000;
	while(mn!=mx){
		ll mid=mn+mx+1;
		mid/=2;

		/*
		無理なのは、以下の2通り
		・中央値以上の個数が確保できない時
		・中央値以上の個数を確保した後、全て1にしても合計が足りない時
		よって
		中央値以上の個数を確保し、その時の合計が大きすぎないか判定する。
		※デカい奴を分割して、中央値を切らないのは問題ではない
		　(それが起きても中央値が増加するだけなので)
		　なお、合計を小さくする必要がある時は切る回数過剰な場合なので
		　切る数不足の際に合計の最小化はしなくて良い(そんなケースはない)
		*/

		//これを割ったら中央値以上の数が減少するライン
		ll stop=mid*2-2;

		//中央値以上の数を減らさず、回数制約を超えるまで大きい方から割る
		map<ll,ll> mp;
		rep(i,n){
			if(a[i]<mid)break;
			mp[a[i]]++;
		}
		ll cnt=m;
		while(cnt!=0&&mp.size()>0){
			auto it=mp.rbegin();
			if(it->first<=stop)break;
			if(it->second<=cnt){
				ll tmp=it->first;
				ll kosuu=it->second;
				mp[tmp/2]+=kosuu;
				mp[(tmp+1)/2]+=kosuu;
				mp.erase(tmp);
				cnt-=kosuu;
			}else{
				ll tmp=it->first;
				mp[tmp/2]+=cnt;
				mp[(tmp+1)/2]+=cnt;
				mp[tmp]-=cnt;
				cnt=0;
			}
		}
		//個数が足りてるかと合計が超えてないか判定
		ll sums=0;
		cnt=0;
		for(auto &val:mp){
			if(val.first<mid)continue;
			if(cnt+val.second<(n+m+1)/2){
				cnt+=val.second;
				sums+=val.first*val.second;
			}else{
				sums+=val.first*((n+m+1)/2-cnt);
				cnt=(n+m+1)/2;
				break;
			}
		}
		if(cnt<(n+m+1)/2||sums>mxsum)mx=mid-1;
		else mn=mid;
	}
	cout<<mx<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t)solve();
	return 0;
}
