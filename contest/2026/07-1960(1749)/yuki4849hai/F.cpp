//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=(n)-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
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
	RollingHash(map<T,ll> h,string shokis=string()){
		table=h;
		rep(i,shokis.size()){
			push_back(shokis[i]);
		}
	}

	//push_backは1文ずつ入れる時に使う。初期化はコンストラクタ。
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

	//半開区間[l,r]
	pair<ll,ll> get_hash(ll l,ll r){
		if(r<l){
			pair<ll,ll>ans={0LL,0LL};
			return(ans);
		}
		r++;
		pair<ll,ll> ans={((hash[r].first-hash[l].first+md)*baseinv[l].first)%md,((hash[r].second-hash[l].second+md)*baseinv[l].second)%md};
		return ans;
	}
	//閉区間[l,r]
	pair<ll,ll> get_revhash(ll l,ll r){
		if(r<l){
			pair<ll,ll>ans={0LL,0LL};
			return(ans);
		}
		r++;
		pair<ll,ll> ans={(rhash[r].first-((rhash[l].first*base[r-l].first)%md)+md)%md,(rhash[r].second-((rhash[l].second*base[r-l].second)%md)+md)%md};
		return ans;
	}

	//閉区間[l,r]が回文か判定する
	bool ispalindrome(ll l,ll r){
		pair<ll,ll> obv=get_hash(l,r);
		pair<ll,ll> rev=get_revhash(l,r);
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
		//大文字の場合等、対応してるかチェックすること。
		table['a'+i]=mt()%1048828087;
		table['0']=mt()%1048828087;
	}
	ll n;
	cin>>n;
	map<pair<ll,ll>,ll> mp;
	ll ans=0;
	while(n--){
		string s;
		cin>>s;
		RollingHash<char> h(table);
		ans++;
		rep(i,s.size()){
			h.push_back(s[i]);
			mp[h.get_hash(0,i)]++;
			ll tmp=mp[h.get_hash(0,i)];
			if(tmp==2){
				ans+=2;
			}
			if(tmp>=3){
				ans++;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
