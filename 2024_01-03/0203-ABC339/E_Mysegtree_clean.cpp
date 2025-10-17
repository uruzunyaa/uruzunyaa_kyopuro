#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000
#define mod 998244353
//#define mod 1000000007

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
struct SegTree{
	ll size;
	ll tall;
    vvl data;
	function<ll(ll,ll)> p;
	//コンストラクタ、セグ木に乗せる値の初期値をa配列にし、putの関数をセグ木に乗せる。
    SegTree(vl a,function<ll(ll,ll)> put) : data(logax(2,a.size())+1) {
		size=a.size();
		tall=logax(2,size)+1;
		p=put;
		ll tmp=size;
		rep(i,tall){
			data[i]=vl(tmp,-inf);
			if(i==0)rep(j,tmp)data[i][j]=a[j];
			else rep(j,tmp) data[i][j]=p(data[i-1][2*j],data[i-1][min(2*j+1,(ll)(data[i-1].size()-1))]);
			tmp=(tmp+1)/2;
		}
	}
	//更新、t番目の値をxにする。
	void update(ll t,ll x){
		rep(i,tall){
			if(i==0)data[i][t]=x;
			else data[i][t]=p(data[i-1][2*t],data[i-1][min(2*t+1,(ll)(data[i-1].size()-1))]);
			t/=2;
		}
	}
	//取得、l~r区間内の最大値を取得する。
	ll get(ll l,ll r){
		r++;
		//lとrが範囲外なら範囲内に正す
		l=max(0LL,l);
		r=min(r,size);
		ll ans=-inf;
		ll h=0;
		ll po=1;
		//出来る限り上に上げきる。
		while(l+(po*2)<=r){
			while(l%(po*2)==0&&l+(po*2)<=r)h++,po*=2;
			ans=p(ans,data[h][l/po]);
			l+=po;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+po>r)h--,po/=2;
			ans=p(ans,data[h][l/po]);
			l+=po;
		}
		return ans;
	}
};

ll put(ll x,ll y){return max(x,y);}

//メイン
int main(){
	ll n,d;
	cin>>n>>d;
	vl a(n);
	rep(i,n)cin>>a[i];
	SegTree seg(vl(600000,0),put);

	rep(i,n){
		ll mx=seg.get(a[i]-d,a[i]+d);
		seg.update(a[i],mx+1);
	}

	cout<<seg.get(1,500000)<<endl;
	return 0;
}
