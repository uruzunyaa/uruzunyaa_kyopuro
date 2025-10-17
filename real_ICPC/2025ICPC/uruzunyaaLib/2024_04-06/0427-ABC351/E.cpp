
#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define inf 4000000000000000000LL

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

//マージソートツリー、構築関数
vvl po(vvl a,vvl b){
	//pa,pbはそれぞれ何個データを取り出したかを記録
	ll pa=0;
	ll pb=0;
	ll sumy=0;
	ll sumx=0;
	vvl res;
	while(pa!=a.size()||pb!=b.size()){
		if(pa!=a.size()&&(pb==b.size()||a[pa]<=b[pb])){
			sumy += a[pa][0];
			sumx += a[pa][1];
			vl tmp={a[pa][0],a[pa][1],sumy,sumx};
			res.push_back(tmp);
			pa++;
		}else{
			sumy += b[pb][0];
			sumx += b[pb][1];
			vl tmp={b[pb][0],b[pb][1],sumy,sumx};
			res.push_back(tmp);
			pb++;
		}
	}
	return res;
}

struct MergeSortTree {
	ll size;
	ll tall;
	vector<vvl> data;

	MergeSortTree(vector<vvl> a){
		ll n = a.size();
		data.resize(power(2, logax(2, n) + 1));
		size = data.size()/2;
		tall = logax(2, size) + 1;
		ll tmp = size;
		data = vector<vvl>(size*2);
		while(tmp != 0){
			if(tmp == size) rep(i, a.size()) data[tmp + i] = a[i];
			else rep(i, tmp) data[tmp + i] = po(data[2 * (tmp + i)], data[2 * (tmp + i) + 1]);
			tmp /= 2;
		}
	}

	//l番目からr番目のノード内で、y座標m以下の値の{個数,x座標合計,y座標合計}を取得する
	vl get(ll l, ll r,ll m){
		r++;
		vl ans = {0,0,0};
		ll pos = l + size;
		ll wid = 1;
		while(l + (wid * 2) <= r){
			while(l % (wid * 2) == 0 && l + (wid * 2) <= r) pos /= 2, wid *= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), vl{m,inf,inf,inf});
			if(it != data[pos].begin()){
				ans[0] += it-data[pos].begin();
				it--;
				ans[1] += (*it)[3];
				ans[2] += (*it)[2];
			}
			pos++;
			l += wid;
		}
		while(l != r){
			while(l + wid > r) pos *= 2, wid /= 2;
			auto it = upper_bound(data[pos].begin(), data[pos].end(), vl{m,inf,inf,inf});
			if(it != data[pos].begin()){
				ans[0] += it-data[pos].begin();
				it--;
				ans[1] += (*it)[3];
				ans[2] += (*it)[2];
			}
			pos++;
			l += wid;
		}
		return ans;
	}
};

int main(){
	ll n;
	cin>>n;
	vector<pair<ll,ll>> xy(n);
	rep(i,n)cin>>xy[i].first>>xy[i].second;
	sort(xy.begin(),xy.end());
	vector<vvl> p(n,vvl(1,vl(4)));
	rep(i,n){
		p[i][0][0]=xy[i].second;
		p[i][0][1]=xy[i].first;
		p[i][0][2]=p[i][0][0];
		p[i][0][3]=p[i][0][1];
	}
	MergeSortTree mst(p);

	ll q;
	cin>>q;
	cout<<fixed<<setprecision(6);
	rep(z,q){
		ll a,b,c,d;
		cin>>a>>b>>c>>d,a--,b--;
		ll l=upper_bound(xy.begin(),xy.end(),make_pair(a,inf))-xy.begin();
		ll r=upper_bound(xy.begin(),xy.end(),make_pair(c,inf))-xy.begin()-1;
		vl up,down;
		if(l<=r){
			up=mst.get(l,r,d);
			down=mst.get(l,r,b);
		}else{
			up={0,0,0};
			down={0,0,0};
		}
		if(up[0]-down[0]==0){
			cout<<"NoPoint"<<endl;
		}else{
			double avex=(double)(up[1]-down[1])/(up[0]-down[0]);
			double avey=(double)(up[2]-down[2])/(up[0]-down[0]);
			cout<<avex<<" "<<avey<<endl;
		}
	}
	return 0;
}
