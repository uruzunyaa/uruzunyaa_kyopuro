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

//メイン
int main(){
	//入力
	ll n,m;
	cin>>n>>m;
	vl x(m);
	//島の番号を0indexに合わせる。
	rep(i,m)cin>>x[i],x[i]--;

	//imos[i]=切断場所を、(i-1)-(i)から、(i)-(i+1)にしたときの変化量。
	vl imos(n,0);
	//1-nの橋を通らない場合を計算。
	ll f=0;
	rep(i,m-1){
		ll a=min(x[i],x[i+1]);
		ll b=max(x[i],x[i+1]);
		//1-nの橋を通らない場合
		ll r=b-a;
		f+=r;
		//通る場合
		ll l=n-r;
		
		//地点A,Bでの変化量を累積する。
		imos[a]+=l-r;
		imos[b]+=r-l;
	}
	//事前計算の変化量を使い、変化量を足しながら最善を見つける。
	ll mn=f;
	rep(i,n-1){
		f+=imos[i];
		mn=min(f,mn);
	}

	cout<<mn<<endl;
	return 0;
}
