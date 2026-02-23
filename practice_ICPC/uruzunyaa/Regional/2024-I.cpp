#include<bits/stdc++.h>
using namespace std;
#define ll int
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

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


ll mx=100000;
set<ll> ans;
vl cnt(mx+1,0);
vvl e(mx+1);
vl a;

void add(ll i){
	ll tmp=a[i];
	for(auto val:e[tmp]){
		cnt[val]++;
		if(cnt[val]==2)ans.insert(val);
	}
}
void erase(ll i){
	ll tmp=a[i];
	for(auto val:e[tmp]){
		cnt[val]--;
		if(cnt[val]==1)ans.erase(val);
	}
}

void addleft(ll l,ll r){
	add(l);
}
void addright(ll l,ll r){
	add(r-1);
}
void eraseleft(ll l,ll r){
	erase(l);
}
void eraseright(ll l,ll r){
	erase(r-1);
}
ll putans(ll i){
	return *ans.rbegin();
}

//メイン
int main(){
	ans.insert(1);
	loop(i,2,mx){
		for(ll j=i;j<=mx;j+=i){
			e[j].push_back(i);
		}
	}

	ll n;
	cin>>n;
	rep(i,n){
		ll aa;
		cin>>aa;
		a.push_back(aa);
	}

	Mo<ll> mos(n,addleft,addright,eraseleft,eraseright,putans);
	ll q;
	cin>>q;
	rep(i,q){
		ll l,r;
		cin>>l>>r;
		l--;
		mos.add(l,r);
	}
	vl fans=mos.execution();
	rep(i,q)cout<<fans[i]<<endl;
	return 0;
}
