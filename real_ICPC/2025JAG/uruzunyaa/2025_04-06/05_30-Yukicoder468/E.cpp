#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

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



vvl g;
vl indextonum;
void dfs(ll node){
	rep(i,g[node].size()){
		dfs(g[node][i]);
	}
	indextonum.push_back(node);
	return;
}

ll sums(ll a,ll b){return a+b;}

//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i],a[i]--;
	

	ll q;
	cin>>q;

	g=vvl(n+q);
	vvl query;
	vl matubi;
	ll b=n;

	rep(i,q){
		vl tmp;
		ll t;
		cin>>t;
		if(t==1){
			ll k;
			cin>>k;
			tmp={1,b};
			if(k==0){
				matubi.push_back(b);
			}else{
				k--;
				g[k].push_back(b);
			}
			b++;
		}else if(t==2){
			tmp={2};
		}else{
			ll k;
			cin>>k;
			tmp={3,k};
		}
		query.push_back(tmp);
	}

	rep(i,n)dfs(a[i]);
	rep(i,matubi.size())dfs(matubi[i]);

	ll alen=indextonum.size();

	vl numtoindex(alen);
	rep(i,alen)numtoindex[indextonum[i]]=i;
	
	vl tmpseg(alen,0);
	rep(i,alen)if(indextonum[i]<n)tmpseg[i]=1;
	SegTree<ll> seg(tmpseg,sums,0);

	ll cnttwo=0;
	rep(i,q){
		if(query[i][0]==1){
			ll k=numtoindex[query[i][1]];
			seg.update(k,1);
		}else if(query[i][0]==2){
			seg.update(cnttwo,0);
			cnttwo++;
		}else{
			ll k=query[i][1];
			ll l=cnttwo,r=alen-1;
			while(l!=r){
				ll mid=(l+r)/2;
				ll tmp=seg.get(0,mid);
				if(tmp<k)l=mid+1;
				else r=mid;
			}
			cout<<indextonum[l]+1<<endl;
		}
	}
	//vdbg(indextonum);
	return 0;
}

