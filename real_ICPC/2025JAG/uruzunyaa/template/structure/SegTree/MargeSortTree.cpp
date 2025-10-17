#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define ll long long
#define vl vector<ll>
#define inf 4000000000000000000LL
#define nopoint 200000000000000.0

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
vector<pair<ll,ll>> po(vector<pair<ll,ll>> x,vector<pair<ll,ll>> y){
	ll px=0;
	ll py=0;
	ll imos=0;
	vector<pair<ll,ll>> res;
	while(px!=x.size()||py!=y.size()){
		if(px!=x.size()&&(py==y.size()||x[px].first<=y[py].first)){
			imos+=x[px].first;
			res.push_back(make_pair(x[px].first,imos));
			px++;
		}else{
			imos+=y[py].first;
			res.push_back(make_pair(y[py].first,imos));
			py++;
		}
	}
	return res;
}

struct MergeSortTree {
	ll size;
	ll tall;
	vector<vector<pair<ll,ll>>> data;

	MergeSortTree(vector<vector<pair<ll,ll>>> a) {
		ll n = a.size();
		data.resize(power(2, logax(2, n) + 1));
		size = data.size()/2;
		tall = logax(2, size) + 1;
		ll tmp = size;
		data = vector<vector<pair<ll,ll>>>(size*2);
		while(tmp != 0){
			if(tmp == size) rep(i, a.size()) data[tmp + i] = a[i];
			else rep(i, tmp) data[tmp + i] = po(data[2 * (tmp + i)], data[2 * (tmp + i) + 1]);
			tmp /= 2;
		}
	}
	pair<ll,ll> get(ll l, ll r, ll m){
		r++;
		double ans = 0;
		ll cnt = 0;
		ll pos = l + size;
		ll wid = 1;
		while(l + (wid * 2) <= r){
			while(l % (wid * 2) == 0 && l + (wid * 2) <= r) pos /= 2, wid *= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), make_pair(m, inf));
			if(it != data[pos].begin()){
				cnt += it-data[pos].begin();
				it--;
				ans += it->second;
			}
			pos++;
			l += wid;
		}
		while(l != r){
			while(l + wid > r) pos *= 2, wid /= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), make_pair(m, inf));
			if(it != data[pos].begin()){
				cnt += it-data[pos].begin();
				it--;
				ans += it->second;
			}
			pos++;
			l += wid;
		}
		return make_pair(ans,cnt);
	}
};

//使用例PGWSC001-Ex
int main(){
	//入力
	ll n;
	cin>>n;
	vector<pair<ll,ll>> xy(n);
	rep(i,n)cin>>xy[i].first>>xy[i].second;
	
	//点をx座標順にソート
	sort(xy.begin(),xy.end());
	vector<vector<pair<ll,ll>>> x(n);

	//y座標を乗せたマージソートツリーを構築
	rep(i,n)x[i].push_back(make_pair(xy[i].second,xy[i].second));
	MergeSortTree mst(x);

	ll q;
	cin>>q;
	cout<<fixed<<setprecision(15);
	rep(z,q){
		ll a,b,c,d;
		cin>>a>>b>>c>>d,a--,b--;
		//x座標
		ll l=upper_bound(xy.begin(),xy.end(),make_pair(a,inf))-xy.begin();
		ll r=upper_bound(xy.begin(),xy.end(),make_pair(c,inf))-xy.begin()-1;

		//y座標合計と個数を取得
		pair<ll,ll> up,down;
		up=mst.get(l,r,d);
		down=mst.get(l,r,b);
		if(up.second-down.second==0){
			cout<<"NoPoint"<<endl;
		}else{
			double avey=(double)(up.first-down.first)/(up.second-down.second);
			cout<<avey<<endl;
		}
	}
	return 0;
}