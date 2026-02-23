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

/// @option_start 使用例

// ll mx(ll a,ll b){
// 	return max(a,b);
// }
// ll checker;
// bool check(ll a){
// 	return (a<checker);
// }

//使用例ACLContestSegTree
// int main(){
// 	ll n,q;
// 	cin>>n>>q;
// 	vl a(n);
// 	rep(i,n)cin>>a[i];
// 	SegTree<ll> seg(a,mx,0);

// 	while(q--){
// 		ll t;
// 		cin>>t;
// 		if(t==1){
// 			ll x,v;
// 			cin>>x>>v;
// 			x--;
// 			seg.update(x,v);
// 		}else if(t==2){
// 			ll l,r;
// 			cin>>l>>r;
// 			l--,r--;
// 			cout<<seg.get(l,r)<<endl;
// 		}else{
// 			ll x,v;
// 			cin>>x>>v;
// 			x--;
// 			checker=v;
// 			ll tmp=seg.max_right(x,check)+2;
// 			tmp=min(tmp,n+1);
// 			cout<<tmp<<endl;
// 		}
// 	}
// 	return 0;
// }
// /// @option_end 使用例

pair<ll,ll> sums(pair<ll,ll> a,pair<ll,ll> b){
	return {a.first+b.first,a.second+b.second};
}

ll checker;
bool check(pair<ll,ll> t){
	return t.first<=checker;
}

//メイン
int main(){
	ll n,q;
	cin>>n>>q;
	vl a(n),b(n);
	rep(i,n)cin>>a[i]>>b[i];

	ll allsum=0;
	multiset<ll>oneset,twoset;
	vector<pair<ll,ll>> vv(1000001,{0,0});
	rep(i,n)vv[a[i]]={vv[a[i]].first+1,vv[a[i]].second+a[i]};
	SegTree<pair<ll,ll>> seg(vv,sums,{0,0});

	rep(i,n){
		if(b[i]==1)oneset.insert(a[i]);
		else twoset.insert(a[i]);
		allsum+=a[i];
	}

	while(q--){
		ll w,x,y;
		cin>>w>>x>>y;
		w--;
		//削除
		{
			if(b[w]==1){
				auto it=oneset.lower_bound(a[w]);
				oneset.erase(it);
			}else{
				auto it=twoset.lower_bound(a[w]);
				twoset.erase(it);
			}
			pair<ll,ll> tmp=seg.get(a[w],a[w]);
			tmp.first--,tmp.second-=a[w];
			seg.update(a[w],tmp);
			allsum-=a[w];
		}
		//更新
		a[w]=x,b[w]=y;
		//追加
		{
			if(b[w]==1){
				oneset.insert(a[w]);
			}else{
				twoset.insert(a[w]);
			}
			pair<ll,ll> tmp=seg.get(a[w],a[w]);
			tmp.first++,tmp.second+=a[w];
			seg.update(a[w],tmp);
			allsum+=a[w];
		}
		ll ans=0;
		if(oneset.size()==0){
			ans=allsum-*twoset.begin();
		}else if(twoset.size()==0){
			ans=0;
		}else if(*oneset.rbegin()<*twoset.begin()){
			checker=twoset.size()-1;
			ll ind=seg.min_left(1000000,check);
			pair<ll,ll> tmp = seg.get(ind,1000000);
			ans+=*oneset.rbegin()+tmp.second;
			ans+=(checker-tmp.first)*(ind-1);
		}else{
			checker=twoset.size();
			ll ind=seg.min_left(1000000,check);
			pair<ll,ll> tmp = seg.get(ind,1000000);
			ans+=tmp.second;
			ans+=(checker-tmp.first)*(ind-1);
		}
		ans+=allsum;
		cout<<ans<<endl;
	}
	return 0;
}
