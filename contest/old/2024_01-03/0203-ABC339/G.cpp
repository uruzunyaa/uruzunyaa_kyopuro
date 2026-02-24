#include<iostream>//入出力
#include<algorithm>//アルゴリズム
#include<vector>//配列
#include<string>//文字列
#include<functional>//関数型変数
#include<set>//セット
#include<unordered_set>//ハッシュセット
#include<map>//木構造マップ
#include<unordered_map>//ハッシュマップ
#include<queue>//キュー、優先度付きキュー
#include<deque>//スタックとキュー
#include<iomanip>//出力形式調整
#include<tuple>//pairの複数型
#include<cmath>//数学。ルートとか
#include<cctype>//大文字小文字のチェックなど
#include<fstream>//ファイル入出力
#include<random>//乱数
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define range(value,range) for(const auto &value : range)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
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
	//セグ木デバッグ用、丸ごと出力
	void print(){
		rep(i,size)cout<<setw(7)<<left<<i;
		cout<<endl;
		ll pos=size;
		rep(i,tall){
			rep(j,size){
				if(j%power(2,i)==0)cout<<setw(7)<<left<<data[pos],pos++;
				else cout<<"       ";
			}
			pos/=4;
			cout<<endl;
		}
	}
};
struct MergeImosTree : SegTree<vector<pair<ll,ll>>>{
	//コンストラクタを継承。
	using SegTree::SegTree;

	//特定の条件に当てはまるものを取得,アドホック実装
	//l~r区間のfirstがm以下の中で最大のsecondを返す
	ll sp_get(ll l,ll r,ll m){
		//lとrが範囲外なら範囲内に正す
		l=max(0LL,l);
		r=min(r,size-1);
		r++;

		ll ans=0;
		ll pos=l+size;
		ll wid=1;
		//出来る限り上に上げきる。
		while(l+(wid*2)<=r){
			while(l%(wid*2)==0&&l+(wid*2)<=r)pos/=2,wid*=2;
			auto it=upper_bound(data[pos].begin(),data[pos].end(),make_pair(m,inf));
			if(it!=data[pos].begin()){
				it--;
				ans+=it->second;
			}
			pos++;
			l+=wid;
		}
		//上げ終わったので今度は下げる
		while(l!=r){
			while(l+wid>r)pos*=2,wid/=2;
			auto it=upper_bound(data[pos].begin(),data[pos].end(),make_pair(m,inf));
			if(it!=data[pos].begin()){
				it--;
				ans+=it->second;
			}
			pos++;
			l+=wid;
		}
		return ans;
	}
	void sp_print(){
		rep(i,size)cout<<setw(7)<<left<<i;
		cout<<endl;
		ll pos=size;
		rep(i,tall){
			ll k=0;
			rep(j,size){
				cout<<setw(7)<<left<<data[pos][k].first;
				k++;
				if((j+1)%power(2,i)==0)pos++,k=0;
			}
			pos/=4;
			cout<<endl;
		}
	}
};
//マージソート、累積和ペアツリー
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
//メイン
int main(){
	ll n;
	cin>>n;
	vector<vector<pair<ll,ll>>> a(n);
	ll aa;
	rep(i,n)cin>>aa,a[i].push_back(make_pair(aa,aa));
	MergeImosTree mit(a,po,vector<pair<ll,ll>>(0));

	ll q,ans=0;
	cin>>q;
	rep(z,q){
		ll f,g,h;
		cin>>f>>g>>h;
		f^=ans;
		g^=ans;
		h^=ans;
		ans=mit.sp_get(f-1,g-1,h);
		cout<<ans<<endl;
	}
	//mit.sp_print();
	return 0;
}