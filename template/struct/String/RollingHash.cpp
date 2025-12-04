#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353LL

random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

template<typename T>
struct RollingHash{
	//桁の進数
	static vector<pair<ll,ll>> base;
	//桁の進数のinv
	static vector<pair<ll,ll>> baseinv;
	//管理のmod
	static ll md;
	
	vector<pair<ll,ll>> hash={{0,0}},rhash={{0,0}};
	map<T,ll> table;

	//(HashTable)
	RollingHash(map<T,ll> h){table=h;}

	void push_back(T c){
		if(base.size()==hash.size()){
			base.push_back({(base.back().first*base[1].first)%md,(base.back().second*base[1].second)%md});
			baseinv.push_back({(baseinv.back().first*baseinv[1].first)%md,(baseinv.back().second*baseinv[1].second)%md});
		}
		ll tmp=hash.size()-1;
		hash.push_back({(hash[tmp].first+base[tmp].first*table[c])%md,(hash[tmp].second+base[tmp].second*table[c])%md});
		rhash.push_back({(rhash[tmp].first*base[1].first+table[c])%md,(rhash[tmp].second*base[1].second+table[c])%md});
	}
	
	void pop_back(){
		hash.pop_back();
		rhash.pop_back();
	}

	pair<ll,ll> get_hash(ll l,ll r){
		pair<ll,ll> ans={((hash[r].first-hash[l].first+md)*baseinv[l].first)%md,((hash[r].second-hash[l].second+md)*baseinv[l].second)%md};
		return ans;
	}

	pair<ll,ll> get_revhash(ll l,ll r){
		pair<ll,ll> ans={(rhash[r].first-((rhash[l].first*base[r-l].first)%md)+md)%md,(rhash[r].second-((rhash[l].second*base[r-l].second)%md)+md)%md};
		return ans;
	}

	bool ispalindrome(ll l,ll r){
		pair<ll,ll> obv={((hash[r].first-hash[l].first+md)*baseinv[l].first)%md,((hash[r].second-hash[l].second+md)*baseinv[l].second)%md};
		pair<ll,ll> rev={(rhash[r].first-((rhash[l].first*base[r-l].first)%md)+md)%md,(rhash[r].second-((rhash[l].second*base[r-l].second)%md)+md)%md};
		return obv==rev;		
	}
	
	ll size(){
		return hash.size()-1;
	}
};
template<typename T>
vector<pair<ll,ll>> RollingHash<T>::base = {{1,1},{999999929,999999937}};
template<typename T>
vector<pair<ll,ll>> RollingHash<T>::baseinv = {{1,1},{209585860,189774042}};
template<typename T>
ll RollingHash<T>::md = 1048828087;

//メイン
int main(){
	map<char,ll> table;
	rep(i,26){
		table['a'+i]=mt()%1048828087;
	}
	RollingHash<char> s(table);
	return 0;
}
