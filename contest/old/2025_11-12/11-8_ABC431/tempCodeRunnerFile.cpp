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


//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//底がaの対数xを計算。ただし小数点は繰り上げ。
ll logax(ll a, ll x){
	if(x<=1)return 0;
	ll result = 1;
	ll power = 1;
	while (power < (x+a-1) / a){
		power *= a;
		result++;
	}
	return result;
}

//powerとlogが前提条件
//セグ木,乗せる値の型が必要
template<typename T>
struct SegTree{
	ll size;
	ll tall;
	vector<T> data;
	function<T(T,T)> p;
	//セグ木に乗せる値の初期値をa配列にし、putの関数をセグ木に乗せる、dをデフォルト値に。
	SegTree(vector<T> a,function<T(T,T)> put,T d) : data(power(2,logax(2,a.size())+1)) {
		size = data.size()/2;
		tall=logax(2,size)+1;
		p=put;
		ll tmp=size;
		data = vector<T>(size*2,d);
		while(tmp!=0){
			if(tmp==size)rep(i,a.size())data[tmp+i]=a[i];
			else rep(i,tmp) data[tmp+i]=p(data[2*(tmp+i)],data[2*(tmp+i)+1]);
			tmp/=2;
		}
	}
	//更新、t番目の値をxにする。
	void update(ll t,T x){
		t+=size;
		while(t!=0){
			if(t>=size)data[t]=x;
			else data[t]=p(data[2*t],data[2*t+1]);
			t/=2;
		}
	}
	//取得、l~r区間内の評価値を取得する。
	T get(ll l,ll r){
		//lとrが範囲外なら範囲内に正す
		l=max(0LL,l);
		r=min(r,size-1);
		r++;
		T ans=data[0];
		ll pos=l+size;
		ll wid=1;
		//出来る限り上に上げきる。
		while(l+(wid*2)<=r){
			while(l%(wid*2)==0&&l+(wid*2)<=r)pos/=2,wid*=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+wid>r)pos*=2,wid/=2;
			ans=p(ans,data[pos]);
			pos++;
			l+=wid;
		}
		return ans;
	}
	// --- ここから追記 ---

	// [l, r] で cond(get(l, r)) が true となる最大の r を返す
	// cond は「区間の集約値」を引数にとり、bool を返す関数。
	// cond が false になる直前の r を返す。存在しなければ l-1 を返す。
	ll max_right(ll l, function<bool(T)> cond) {
		if(l < 0 || l >= size) return -1;
		T acc = data[0]; // 単位元扱い
		ll pos = l + size;
		while(true){
			// 現在ノードの値と結合しても条件を満たすか？
			if(cond(p(acc, data[pos]))){
				acc = p(acc, data[pos]);
				// 右に進む
				if(pos == 1) return size - 1; // root到達（右端）
				// posが右子の時は、親に上がる
				if(pos % 2 == 1) pos++;
				else{
					// 親に戻る
					while(pos % 2 == 0) pos >>= 1;
					pos++;
				}
			} else {
				// これ以上進めない
				while(pos < size){
					pos <<= 1; // 左子に潜る
					if(cond(p(acc, data[pos]))){
						acc = p(acc, data[pos]);
						pos++;
					}
				}
				return pos - size - 1;
			}
			if(pos >= 2*size) return size-1;
		}
	}

	// [l, r] で cond(get(l, r)) が true となる最小の l を返す
	// cond は「区間の集約値」を引数にとり、bool を返す関数。
	// cond が false になる直後の l を返す。存在しなければ r+1 を返す。
	ll min_left(ll r, function<bool(T)> cond) {
		if(r < 0 || r >= size) return -1;
		T acc = data[0]; // 単位元
		ll pos = r + size;
		while(true){
			if(cond(p(data[pos], acc))){
				acc = p(data[pos], acc);
				if(pos == 1) return 0;
				if(pos % 2 == 0) pos--;
				else{
					while(pos % 2 == 1) pos >>= 1;
					pos--;
				}
			} else {
				while(pos < size){
					pos = pos * 2 + 1;
					if(cond(p(data[pos], acc))){
						acc = p(data[pos], acc);
						pos--;
					}
				}
				return pos - size + 1;
			}
			if(pos <= 0) return 0;
		}
	}
};

ll sum(ll a,ll b){
	return a+b;
}

ll nowk;
bool check(ll sum){
	return sum<nowk;
}


//メイン
int main(){
	vl v={0,0,0,1};
	SegTree<ll> seg(v,sum,0);
	nowk=1;
	ll tmp=seg.max_right(2,check);
	cout<<tmp<<endl;
	return 0;
}
