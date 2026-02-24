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
//#define mod 998244353LL
#define mod 1000000007LL


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
vvl g;
vector<unordered_map<ll,pair<ll,ll>>> dp;
//dp[i][j]=頂点jが親である時の、iを頂点とする部分木の{答え、頂点数}

pair<ll,ll> dfs(ll par,ll now){
	//既に計算済みな場合
	if(dp[now].count(par))return dp[now][par];
	
	//計算済みではないが、何かしら計算済みな場合
	if(dp[now].size()){
		//根とした場合が計算されていないなら計算する
		if(!dp[now].count(-1)){
			pair<ll,ll> ans={1,0};
			rep(i,g[now].size()){
				pair<ll,ll> tmp = dfs(now,g[now][i]);
				ans.second+=tmp.second;
				ans.first*=tmp.first;
				ans.first%=mod;
				ans.first*=ncrmod(ans.second,tmp.second);
				ans.first%=mod;
			}
			ans.second++;
			dp[now][-1]=ans;
			
			//デバッグ
			//cout<<"dp["<<now<<"]["<<-1<<"]={"<<dp[now][-1].first<<","<<dp[now][-1].second<<"}"<<endl;

			if(par==-1)return ans;
		}
		//根との差分を引く
		pair<ll,ll> tmp = dp[par][now];
		pair<ll,ll> ans=dp[now][-1];
		ans.second--;
		ans.first*=power_mod(ncrmod(ans.second,tmp.second),mod-2);
		ans.first%=mod;
		ans.first*=power_mod(tmp.first,mod-2);
		ans.first%=mod;
		ans.second-=tmp.second;
		ans.second++;
		dp[now][par]=ans;

		//デバッグ
		//cout<<"dp["<<now<<"]["<<par<<"]={"<<dp[now][par].first<<","<<dp[now][par].second<<"}"<<endl;
		

		return ans;
	}

	//初計算の場合(普通の木DP)
	pair<ll,ll> ans={1,0};
	rep(i,g[now].size()){
		if(par==g[now][i])continue;
		pair<ll,ll> tmp = dfs(now,g[now][i]);
		ans.second+=tmp.second;
		ans.first*=tmp.first;
		ans.first%=mod;
		ans.first*=ncrmod(ans.second,tmp.second);
		ans.first%=mod;
	}
	ans.second++;
	dp[now][par]=ans;

	//デバッグ
	//cout<<"dp["<<now<<"]["<<par<<"]={"<<dp[now][par].first<<","<<dp[now][par].second<<"}"<<endl;

	return ans;
}

//メイン
int main(){
	cin>>n;
	g = vvl(n);
	dp = vector<unordered_map<ll,pair<ll,ll>>>(n);
	
	rep(i,n-1){
		ll a,b;
		cin>>a>>b;
		a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	rep(i,n){
		//回答モード
		cout<<dfs(-1,i).first<<endl;
		
		//デバッグモード
		//dfs(-1,i);
	}

	//dp配列を丸ごとデバッグする奴

	// rep(i,n){
	// 	loop(j,-1,n-1){
	// 		if(dp[i].count(j))cout<<"{"<<dp[i][j].first<<","<<dp[i][j].second<<"} ";
	// 		else cout<<"{-1,-1} ";
	// 	}
	// 	cout<<endl;
	// }

	
	return 0;
}
