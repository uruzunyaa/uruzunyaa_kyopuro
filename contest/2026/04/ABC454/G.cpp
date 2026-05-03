//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll int
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

//メイン
int main(){
	ll n;
	long long seed,M,f;
	cin>>n>>seed>>M>>f;
	vl p(n,-1),c(n);

	long long state = seed;

	loop(i,1,n-1){
		if (i < M)cin>>p[i],p[i]--;
		else{
			p[i] = (state % (i));
		    state = (state * 1103515245 + 12345) % (1LL<<31);
		}
	}
 
	rep(i,n){
		if (i < M)cin>>c[i],c[i]--;
		else{
			c[i] = (state % f);
    		state = (state * 1103515245 + 12345) %(1LL<<31);
		}
    }

	vvl g(n);
	loop(i,1,n-1)g[p[i]].push_back(i);
	long long ans=0;
	vl m(n,1),k(n,1);
	vector<unordered_map <ll,ll>> mp(n);
	rrep(i,n){
		mp[i][c[i]]++;
		ll sw=i,swsiz=1,sizesum=1;
		//最もmapサイズが大きい奴にswapする
		for(auto val:g[i]){
			sizesum+=mp[val].size();
			if(mp[val].size()>swsiz){
				sw=val;
				swsiz=mp[val].size();
			}
		}
		if(sw!=i){
			swap(mp[sw],mp[i]);
			swap(m[sw],m[i]);
			swap(k[sw],k[i]);
		}
		
		mp[i].reserve(sizesum);
		for(auto val:g[i]){
			for(auto &mpval:mp[val]){
				ll& tmp = mp[i][mpval.first];
				tmp += mpval.second;
				if(tmp>m[i]){
					m[i]=tmp;
					k[i]=1;
				}else if(tmp==m[i]){
					k[i]++;
				}
			}
			unordered_map<ll,ll>().swap(mp[val]);
		}
		ans+=((long long)(m[i]^(i+1)))*((long long)(k[i]^(i+1)));
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
