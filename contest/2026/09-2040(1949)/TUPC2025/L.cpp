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
#define inf 1000000000LL
//#define inf 10LL
#define mod 998244353LL
//#define mod 1000000007LL
#define eps 0.000000001
#define circlepi 3.14159265358979323846
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


map<ll,ll> mp;

ll ask(ll x){
	if(mp.count(x))return mp[x];
	cout<<"? "<<x<<endl;
	ll ans;
	cin>>ans;
	mp[x]=ans;
	return ans;
}
void putans(vl a){
	cout<<"!";
	rep(i,a.size()){
		cout<<" "<<a[i];
	}
	cout<<endl;
}

//メイン
int main(){
	ll n;
	cin>>n;
	map<ll,pair<ll,ll>> katamuki;
	katamuki[-n]={0,1};
	katamuki[n]={inf,inf+1};

	ll res=ask(1);
	mp[inf]=((inf-1)*n)-res;

	ll k=-n;
	while(k<n){
		if(katamuki.count(k)){
			k+=2;
			continue;
		}
		auto it=katamuki.lower_bound(k);
		ll rightnum=it->first;
		ll rightind=it->second.first;
		ll rightsum=mp[rightind];
		it--;
		ll leftnum=it->first;
		ll leftind=it->second.second;
		ll leftsum=mp[leftind];

		ll sum=rightsum-leftsum;
		//ll nagasa=rightind-leftind;

		//小さい方を伸ばして矛盾しない最大indexを求める。
		ll mx=rightind-1,mn=leftind;
		while(mn<mx){
			ll mid=mn+mx+1;
			mid/=2;
			ll tmp=(mid-leftind)*leftnum+(rightind-mid)*rightnum;
			if(tmp<sum)mx=mid-1;
			else mn=mid;
		}
		ll nowkatamuki=ask(mx+1)-ask(mx);
		katamuki[nowkatamuki]={mx,mx+1};
	}

	vl ans;

	//復元
	k=-n;
	while(k<n){
		ll rightnum=k+2;
		ll rightind=katamuki[k+2].first;
		ll rightsum=mp[rightind];
		
		ll leftnum=k;
		ll leftind=katamuki[k].second;
		ll leftsum=mp[leftind];

		ll sum=rightsum-leftsum;
		//ll nagasa=rightind-leftind;

		//小さい方を伸ばして矛盾しない最大indexを求める。
		ll mx=rightind,mn=leftind;
		while(mn<mx){
			ll mid=mn+mx+1;
			mid/=2;
			ll tmp=(mid-leftind)*leftnum+(rightind-mid)*rightnum;
			if(tmp<sum)mx=mid-1;
			else mn=mid;
		}
		
		ans.push_back(mn);
		k+=2;
	}

	putans(ans);

	// for(auto val:katamuki){
	// 	cout<<val.first<<":"<<val.second.first<<" "<<val.second.second<<endl;
	// }
	
	return 0;
}
