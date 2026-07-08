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

ll bitm=3;

void alice(){
	ll x;
	cin>>x;
	ll now=0;
	ll i=bitm;
	while(i>=-1){
		if(now==x){
			cout<<"answer"<<endl;
			return;
		}
		bool f=false;
		if((now<<i)==x){
			f=true;
		}
		if(f){
			cout<<"double"<<endl;
			i--;
		}else if((((1LL<<(i+1))&x)==0LL)&&(2LL&now)){
			cout<<"minus"<<endl;
			now--;
		}else{
			cout<<"plus"<<endl;
			now++;
		}
		string s;
		cin>>s;
		if(s=="answer"){
			return;
		}
		now*=2;
		i--;
	}
}
void bob(){
	ll i=0;
	while(i<bitm){
		string s;
		cin>>s;
		if(s=="double"){
			i++;
		}
		if(s=="answer"){
			return;
		}
		if(i==bitm){
			cout<<"answer"<<endl;
			return;
		}
		cout<<"double"<<endl;
		i++;
	}
	string s;
	cin>>s;
	if(s=="answer"){
		return;
	}
	cout<<"answer"<<endl;
	return;
}

//メイン
int main(){
	string p;
	ll t;
	cin>>p>>t;
	rep(i,t){
		if(p=="Alice")alice();
		else bob();
	}
	return 0;
}
