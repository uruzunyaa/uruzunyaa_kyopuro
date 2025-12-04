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
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//Tが各クエリの答え方の形式。
template<typename T>
struct Mo {
	int n;
	vector<pair<int,int>> lr;
	function<void(int,int)> AL,AR,EL,ER;
	function<T(int)> put;

	//Addは追加後を、eraseはこれから消す座標を渡す。
	Mo(
		int N,
		function<void(int,int)> add_left,
		function<void(int,int)> add_right,
		function<void(int,int)> erase_left,
		function<void(int,int)> erase_right,
		function<T(int)> put_ans
	) : n(N) {
		AL = add_left;
		AR = add_right;
		EL = erase_left;
		ER = erase_right;
		put = put_ans;
	}

	// [l, r)形式で区間クエリを入れる
	void add(int l, int r) { 
		lr.emplace_back(l, r);
	}

	vector<T> execution() {
		int q = (int) lr.size();
		int blocksize = sqrt(n)+1;
		vector<int> ord(q);
		iota(begin(ord), end(ord), 0);
		sort(begin(ord), end(ord), [&](int a, int b) {
			int ablock = lr[a].first / blocksize, bblock = lr[b].first / blocksize;
			if(ablock != bblock) return ablock < bblock;
			return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
		});
		int l = 0, r = 0;
		vector<T> ans(q);
		for(auto idx : ord) {
			while(l > lr[idx].first) AL(--l,r);
			while(r < lr[idx].second) AR(l,++r);
			while(l < lr[idx].first) EL(l++,r);
			while(r > lr[idx].second) ER(l,r--);
			ans[idx] = put(idx);
		}
		return ans;
	}
};

//以下使用例、Sum of Subarray(423-E)
//問題概要:数列Aが与えられて、その後区間クエリl,rの全ての連続部分列の和を各クエリについて答えよ
//解法:右と左の差分更新をクエリ平方分割で。

ll ans;
vl onesum,twosum,revonesum,revtwosum;

void addl(ll l,ll r){
	ans+=twosum[r]-twosum[l]-(r-l)*onesum[l];
}
void erasel(ll l,ll r){
	ans-=twosum[r]-twosum[l]-(r-l)*onesum[l];
}
void addr(ll l,ll r){
	ans+=revtwosum[l]-revtwosum[r]-(r-l)*revonesum[r];
}
void eraser(ll l,ll r){
	ans-=revtwosum[l]-revtwosum[r]-(r-l)*revonesum[r];
}
ll calc(ll index){
	return ans;
}


//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl a(n);
	rep(i,n)cin>>a[i];

	onesum=vl(n+1,0);
	twosum=vl(n+1,0);
	revonesum=vl(n+1,0);
	revtwosum=vl(n+1,0);
	

	rep(i,n){
		onesum[i+1]=onesum[i]+a[i];
		twosum[i+1]=twosum[i]+onesum[i+1];
		revonesum[n-i-1]=revonesum[n-i]+a[n-i-1];
		revtwosum[n-i-1]=revtwosum[n-i]+revonesum[n-i-1];
	}

	ans=0;
	Mo<ll> mo(n,addl,addr,erasel,eraser,calc);

	while(q--){
		ll l,r;
		cin>>l>>r;
		l--;
		mo.add(l,r);
	}
	vl fans=mo.execution();

	rep(i,fans.size())cout<<fans[i]<<endl;
	return 0;
}
