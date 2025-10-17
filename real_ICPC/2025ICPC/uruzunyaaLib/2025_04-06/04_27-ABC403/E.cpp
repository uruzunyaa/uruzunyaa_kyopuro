#pragma GCC optimize("O3")
#include<bits/stdc++.h>
//#include<boost/multiprecision/cpp_int.hpp>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
//#define bbi boost::multiprecision::cpp_int
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

//桁の進数
ll md0=999999937;
ll md1=999999929;
//管理のmod
ll md2=1048828087;

//メイン
int main(){
	unordered_map<ll,pair<ll,ll>> stir;
	rep(i,26){
		stir['a'+i]={mt()%md2,mt()%md2};
	}
	set<pair<ll,ll>> nglist;
	map<pair<ll,ll>,ll> count;

	ll q;
	cin>>q;
	ll ans=0;
	while(q--){
		ll t;
		string s;
		cin>>t>>s;
		pair<ll,ll> hash={0,0};
		bool f=false;
		vector<pair<ll,ll>> tmp;
		rep(i,s.size()){
			hash.first*=md0;
			hash.second*=md1;
			hash.first+=stir[s[i]].first;
			hash.second+=stir[s[i]].second;
			hash.first%=md2;
			hash.second%=md2;
			tmp.push_back(hash);
			if(nglist.count(hash))f=true;
		}
		if(f){
			cout<<ans<<endl;
			continue;
		}
		if(t==1){
			ans-=count[hash];
			rep(i,tmp.size()){
				count[tmp[i]]-=count[hash];
			}
			nglist.insert(hash);
		}else{
			ans++;
			rep(i,tmp.size()){
				count[tmp[i]]++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
