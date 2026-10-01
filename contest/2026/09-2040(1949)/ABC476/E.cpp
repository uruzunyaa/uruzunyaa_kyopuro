#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>

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
//max_rightやmin_left使用時には2の累乗に拡張されている事に注意
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
	/// @option_start max_right,min_left

	// [l, r] (両端含む) で cond(get(l, r)) が true となる最大の r を返す
	// cond は「区間の集約値 -> bool」
	// 見つからなければ l-1 を返す
	ll max_right(ll l, function<bool(T)> cond){
		if (l < 0) l = 0;
		if (l >= size) return size - 1;
		T sm = data[0];
		ll i = l + size; 
		do {
			while ((i & 1) == 0) i >>= 1;
			if (!cond(p(sm, data[i]))) {
				while (i < size) {
					i <<= 1;
					if (cond(p(sm, data[i]))) {
						sm = p(sm, data[i]);
						i++;
					}
				}
				return i - size - 1;
			}
			sm = p(sm, data[i]);
			i++;
		} while ((i & -i) != i);
		return size - 1;
	}


	// [l, r] (両端含む) で cond(get(l, r)) が true となる最小の l を返す
	// 見つからなければ r+1 を返す
	ll min_left(ll r, function<bool(T)> cond){
		if (r < 0) return 0;
		if (r >= size) r = size - 1;
		T sm = data[0];               // 単位元
		ll i = r + 1 + size;          // ACLは [l, r) なので r+1 から始める

		do {
			i--;                      // まず一つ左へ
			while (i > 1 && (i & 1)) i >>= 1;  // 右子を抜けて親に上がる
			if (!cond(p(data[i], sm))) {
				// ここから下に降りてちょうど壊れる左端を探す
				while (i < size) {
					i = i * 2 + 1;    // 右子へ
					if (cond(p(data[i], sm))) {
						sm = p(data[i], sm);
						i--;          // 左兄弟へ
					}
				}
				return i + 1 - size;
			}
			sm = p(data[i], sm);
		} while ((i & -i) != i);

		return 0;
	}
	/// @option_end max_right,min_left
};
#define inf 4000000000000000000LL

vl e={inf,0,-inf,0};
vl minmaxs(vl a,vl b){
	vl ans(4);
	if(a[0]<b[0]){
		ans[0]=a[0];
		ans[1]=a[1];
	}else{
		ans[0]=b[0];
		ans[1]=b[1];
	}
	if(a[2]>b[2]){
		ans[2]=a[2];
		ans[3]=a[3];
	}else{
		ans[2]=b[2];
		ans[3]=b[3];
	}
	return ans;
}


int main(){
	ll n,m;
	cin>>n>>m;
	vl p(n);
	rep(i,n)cin>>p[i];

	vvl vs;
	rep(i,n){
		vs.push_back({p[i],i,p[i],i});
	}
	SegTree<vl> seg(vs,minmaxs,e);

	rep(i,m){
		ll l,r;
		cin>>l>>r;
		l--,r--;
		vl tmp=seg.get(l,r);
		seg.update(tmp[1],{tmp[2],tmp[1],tmp[2],tmp[1]});
		seg.update(tmp[3],{tmp[0],tmp[3],tmp[0],tmp[3]});
	}

	rep(i,n){
		vl tmp=seg.get(i,i);
		cout<<tmp[0]<<" ";
	}
	cout<<endl;
	return 0;
}