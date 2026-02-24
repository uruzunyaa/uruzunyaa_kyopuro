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


//マージソートツリー
//出来る事、数列A_l~A_rの中で、値がx以下の要素の合計を log^2(n)で求めれる。 

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

//転倒数を求める
ll inversion_number(vl &v) {
	int n = v.size();
	if (n == 1) return 0;
	vl v1(v.begin(), v.begin() + n / 2);
	vl v2(v.begin() + n / 2, v.end());
	ll res = inversion_number(v1) + inversion_number(v2);
	int p = 0, q = 0;
	for (int i = 0; i < n; i++) {
		if (q == v2.size() || (p < v1.size() && v1[p] <= v2[q])) {
			v[i] = v1[p++];
		}else {
			v[i] = v2[q++];
			res += v1.size() - p;
		}
    }
    return res;
}

//多重集合が一致する事を前提とする。
ll inversion_distance(vl a,vl b){
	ll n=a.size();
	map<ll,queue<ll>> mp;
	rep(i,n){
		mp[a[i]].push(i);
	}
	rep(i,n){
		ll tmp=mp[b[i]].front();
		mp[b[i]].pop();
		b[i]=tmp;
	}
	return inversion_number(b);
}

void solve(){
	ll n,k;
	cin>>n>>k;
	vl a(n),b(n);
	rep(i,n)cin>>a[i];
	rep(i,n)cin>>b[i];

	map<ll,ll> mae;
	vector<pair<ll,ll>> querys;
	rep(i,n){
		if(mae.count(a[i])){
			querys.push_back({mae[a[i]],i});
		}
		mae[a[i]]=i;
	}

	map<ll,queue<ll>> mp;
	
	rep(i,n){
		mp[b[i]].push(i);
	}
	rep(i,n){
		ll tmp=mp[a[i]].front();
		mp[a[i]].pop();
		a[i]=tmp;
	}

	vl acopy=a;
	ll inv=inversion_number(acopy);
	ll mn=inf;

	vector<vector<pair<ll,ll>>> v(n);
	rep(i,n)v[i].push_back({a[i],a[i]});
	MergeSortTree mst(v);

	rep(i,querys.size()){
		ll tmp=mst.get(querys[i].first,querys[i].second,a[querys[i].second]).second;
		tmp-=mst.get(querys[i].first,querys[i].second,a[querys[i].first]).second;
		mn=min(mn,tmp);
	}

	ll ans=inf;
	if(k%2==0){
		if(inv%2==0){
			ans=min(ans,(inv+k-1)/k);
		}
	}else{
		ll tmp=(inv+k-1)/k;
		if(tmp%2!=inv%2)tmp++;
		ans=min(tmp,ans);
	}

	//偶奇反転出来る場合
	if(mn!=inf){
		inv+=mn*2-1;
		if(k%2==0){
			if(inv%2==0){
				ans=min(ans,(inv+k-1)/k);
			}
		}else{
			ll tmp=(inv+k-1)/k;
			if(tmp%2!=inv%2)tmp++;
			ans=min(tmp,ans);
		}
	}
	if(ans==inf)cout<<-1<<endl;
	else cout<<ans<<endl;
}

//メイン
int main(){
	ll t;
	cin>>t;
	rep(i,t){
		solve();
	}
	return 0;
}
