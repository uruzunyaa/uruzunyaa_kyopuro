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
#define mod 998244353LL


// nのk乗をmodで割った余りを計算
ll power_mod(ll n, ll k){
	long long result = 1;
	while (k > 0){
		if ((k&1) ==1)result=(result*n)%mod;
		n=n*n%mod;
		k >>= 1;
	}
	return result;
}


//他にpower_modは必要
ll ncrmod_max=200000;
bool use_ncrmod = false;
unordered_map<ll,ll> chash_ncrmod;
unordered_map<ll,ll> chash_invmod;
ll ncrmod(ll n,ll r){
	//nCr = n! / r! / (n-r)!
	if(!use_ncrmod){
		chash_ncrmod[0]=1;
		chash_invmod[0]=1;
		loop(i,1,ncrmod_max){
			chash_ncrmod[i]=chash_ncrmod[i-1]*i;
			chash_ncrmod[i]%=mod;
		}
		loop(i,0,ncrmod_max){
			chash_invmod[i]=power_mod(chash_ncrmod[i],mod-2);
		}
		use_ncrmod=true;
	}
	ll ans=chash_ncrmod[n];
	ans*=chash_invmod[r];
	ans%=mod;
	ans*=chash_invmod[n-r];
	ans%=mod;
	return ans;
}

ll n;
vector<vector<pair<ll,ll>>> g;
vector<unordered_map<ll,pair<ll,ll>>> dp;
//dp[i][j]=頂点jが親である時の、iを頂点とする部分木の{答え、頂点数}

pair<ll,ll> dfs(ll par,ll now,ll costs){
	//既に計算済みな場合
	if(dp[now].count(par))return dp[now][par];
	
	//計算済みではないが、何かしら計算済みな場合
	if(dp[now].size()){
		//根とした場合が計算されていないなら計算する
		if(!dp[now].count(-1)){
			pair<ll,ll> ans={0,1};
			rep(i,g[now].size()){
				pair<ll,ll> tmp = dfs(now,g[now][i].first,g[now][i].second);
				ans.second+=tmp.second;
				ans.second%=mod;
				ans.first+=tmp.first;
				ans.first%=mod;
				ans.first+=tmp.second*g[now][i].second;
				ans.first%=mod;
			}
			dp[now][-1]=ans;
			
			if(par==-1)return ans;
		}
		//根との差分を引く
		pair<ll,ll> tmp = dp[par][now];
		pair<ll,ll> ans=dp[now][-1];

		ans.second+=mod-tmp.second;
		ans.second%=mod;
		ans.first+=mod-tmp.first;
		ans.first%=mod;
		ans.first+=mod-tmp.second*costs;
		ans.first%=mod;
		
		//記録
		dp[now][par]=ans;

		return ans;
	}

	//初計算の場合(普通の木DP)
	pair<ll,ll> ans={0,1};
	rep(i,g[now].size()){
		if(par==g[now][i].first)continue;
		pair<ll,ll> tmp = dfs(now,g[now][i].first,g[now][i].second);
		ans.second+=tmp.second;
		ans.second%=mod;
		ans.first+=tmp.first;
		ans.first%=mod;
		ans.first+=tmp.second*g[now][i].second;
		ans.first%=mod;
	}
	dp[now][par]=ans;
	return ans;
}

//by https://atcoder.jp/contests/abc160/submissions/64848049


//メイン
int main(){
	cin>>n;
	g = vector<vector<pair<ll,ll>>>(n);
	dp = vector<unordered_map<ll,pair<ll,ll>>>(n);
	
	rep(i,n-1){
		ll a,b,d;
		cin>>a>>b>>d;
		a--,b--;
		g[a].push_back({b,d});
		g[b].push_back({a,d});
	}
	ll ans=0;
	ll base=1;
	loop(i,1,n-1){
		base*=i;
		base%=mod;
	}
	rep(i,n){
		//回答モード
		ans+=dfs(-1,i,0).first*base;
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
