#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
#define loop(i,m,n) for(ll i=m;i<=(ll)n;i++)
#define rloop(i,m,n) for(ll i=m;i>=(ll)n;i--)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
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

bool st(RollingHash<char> a,RollingHash<char> b){
	return a.size()<b.size();
}

//メイン
int main(){
	map<char,ll> table;
	rep(i,26){
		table['a'+i]=mt()%1048828087;
	}

	ll n;
	cin>>n;
	vector<RollingHash<char>> s(n,RollingHash<char>(table));
	rep(i,n){
		string ss;
		cin>>ss;
		rep(j,ss.size())s[i].push_back(ss[j]);
	}
	sort(s.rbegin(),s.rend(),st);

	//内包されてる文字を除く
	rrep(i,n){
		bool f=false;
		pair<ll,ll> hash=s[i].get_hash(0,s[i].size());
		rep(j,i){
			loop(k,0,s[j].size()-s[i].size()){
				if(hash==s[j].get_hash(k,k+s[i].size()))f=true;
			}
		}
		if(f)s.erase(s.begin()+i);
	}
	n=s.size();
	
	//cost[i][j]=i番目の文字列の後ろにj番目の文字列を連結する時の、最小増加文字数
	vvl cost(n,vl(n,inf));

	rep(i,n)rep(j,n){
		if(i==j)continue;

		rep(k,min(s[i].size(),s[j].size())){
			if(s[i].get_hash(s[i].size()-k,s[i].size())==s[j].get_hash(0,k)){
				cost[i][j]=s[j].size()-k;
			}
		}
	}

	//文字列上の巡回セールスマン的な感じ
	//dp[i][j]=使った文字の集合がiで、最後にjを使った時の最小文字数
	vvl dp(1LL<<n,vl(n,inf));
	
	rep(i,(1LL<<n)){
		if(i==0){
			rep(j,n)dp[1LL<<j][j]=s[j].size();
			continue;
		}

		rep(j,n){
			if(dp[i][j]==inf)continue;
			rep(k,n){
				if((1LL<<k)&i)continue;
				dp[i+(1<<k)][k]=min(dp[i+(1<<k)][k],dp[i][j]+cost[j][k]);
			}
		}
	}
	ll ans=inf;
	rep(i,n)ans=min(ans,dp[(1<<n)-1][i]);
	cout<<ans<<endl;
	return 0;
}
