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

class Point{
public:
	ll x,y;
	bool check=false;
};

//aの方が小さいか。
bool check(Point a, Point b){
	
	if(b.check)return false;
	if(a.check)return true;

	if(a.x*b.x<0){
		return a.x>0;
	}else if(a.x*b.x==0){
		if(a.x==0&&b.x==0){
			return (a.y>0&&b.y<0);
		}else if(a.x==0){
			if(a.y>0)return true;
			if(b.x<0)return true;
			return false;
		}else {
			if(b.y>0)return false;
			if(a.x<0)return false;
			return true;
		}
	}
	//象限が同じ場合
	return a.y*b.x>a.x*b.y;
}

//他の情報持たせたい時とかは、Point構造体に追加する事。
//真上(0,1)が0度原点で時計周りに偏角ソートする。
vector<Point> argument_sort(vector<Point> p) {
    sort(p.begin(), p.end(), check);
	return p;
}


//使ってるライブラリの置き場
//https://github.com/uruzunyaa/uruzunyaa_kyopuro

//メイン(N点読み込んでソートする例)
int main(){
	ll n;
	cin>>n;
	vector<Point> p;
	vl a(n),b(n);
	rep(i,n){
		cin>>a[i]>>b[i];
		p.push_back({a[i],b[i]});
	}
	p=argument_sort(p);
	return 0;
}
