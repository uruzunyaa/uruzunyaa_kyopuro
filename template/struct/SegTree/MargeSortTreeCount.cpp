#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//マージソートツリー
//数列A_l~A_rの中で、値がm以下の要素の数を log^2(n)で求めれる。 
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
	ll result = 0;
	ll power = 1;
	while (power < x){
		power *= a;
		result++;
	}
	return result;
}

//マージソートツリー,構築関数
vl po(vl x,vl y){
	ll px=0;
	ll py=0;
	vl res;
	while(px!=x.size()||py!=y.size()){
		if(px!=x.size()&&(py==y.size()||x[px]<=y[py])){
			res.push_back(x[px]);
			px++;
		}else{
			res.push_back(y[py]);
			py++;
		}
	}
	return res;
}

struct MergeSortTreeCount {
	ll size;
	ll tall;
	vvl data;

	MergeSortTreeCount(vvl a){
		ll n = a.size();
		data.resize(power(2, logax(2, n) + 1));
		size = data.size()/2;
		tall = logax(2, size) + 1;
		ll tmp = size;
		data = vvl(size*2);
		while(tmp != 0){
			if(tmp == size) rep(i, a.size()) data[tmp + i] = a[i];
			else rep(i, tmp) data[tmp + i] = po(data[2 * (tmp + i)], data[2 * (tmp + i) + 1]);
			tmp /= 2;
		}
	}
	//l以上r以下の、要素で、m以下の値を持つ個数を取得
	ll get(ll l, ll r, ll m){
		r++;
		ll cnt = 0;
		ll pos = l + size;
		ll wid = 1;
		while(l + (wid * 2) <= r){
			while(l % (wid * 2) == 0 && l + (wid * 2) <= r) pos /= 2, wid *= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), m);
			cnt += it-data[pos].begin();
			pos++;
			l += wid;
		}
		while(l != r){
			while(l + wid > r) pos *= 2, wid /= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), m);
			cnt += it-data[pos].begin();
			pos++;
			l += wid;
		}
		return cnt;
	}
};

//これは例の問題用でMargeSortTreeには関係なし
vl nearest_larger(vl a){
	ll n=a.size();
	vl mae(n);
	vector<pair<ll,ll>> tmp;
	tmp.push_back({inf,-1});
	rep(i,n){
		//この下の不等号が、無視する条件。
		while(tmp.back().first<a[i])tmp.pop_back();
		mae[i]=tmp.back().second;
		tmp.push_back({a[i],i});
	}
	return mae;
}

//使用例AWC172-E
int main(){
	ll n,q;
	cin>>n>>q;
	vl a(n);
	rep(i,n)cin>>a[i];

	vl b=nearest_larger(a);

    //値一個の配列の配列を渡す。
	vvl v(n);
	rep(i,n)v[i].push_back(b[i]);
	MergeSortTreeCount mst(v);

	ll ans=0;
	
    while(q--){
		ll l,r;
		cin>>l>>r;
		l--,r--;
        //[l,r]でl-1以下の値の個数を数える。
		ans=mst.get(l,r,l-1);
		cout<<ans<<endl;
	}
	return 0;
}