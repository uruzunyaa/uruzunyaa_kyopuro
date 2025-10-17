//#pragma GCC optimize("O3")
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
#define eps 0.000000001

//#define mod 1000000007LL
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード

ll solve(){
	ll s,n,t,p,m;
	string weekday,time;
	cin>>s>>n>>t>>weekday>>time>>p>>m;
	if(s==0){return 1;}

	double ans=0;
	
	rep(i,7*24*60){
		ll cnt=0;

		//i分ずらした所から、m回開始
		rep(j,m){
			ll start=i+j*t;
			ll end=i+j*t+s;
			if(weekday=="All"){
				if(time=="All"){
					cnt++;
				}else{
					if(end-start<12*60&&start%(24*60)<12*60&&end%(24*60)<12*60)cnt++;
				}
			}else{
				if(time=="All"){
					if(end-start<24*60&&start%(7*24*60)<24*60&&end%(7*24*60)<24*60)cnt++;
				}else{
					if(time=="Day"){
						if(end-start<12*60&&start%(7*24*60)<12*60&&end%(7*24*60)<12*60)cnt++;
					}else{
						if(end-start<6*60&&start%(7*24*60)<6*60&&end%(7*24*60)<6*60)cnt++;
						else if(end-start<6*60&&18*60<=start%(7*24*60)&&start%(7*24*60)<24*60&&18*60<=end%(7*24*60)&&end%(7*24*60)<24*60)cnt++;
					}
				}
			}
		}
		
		//1回に変化しない確率
		double kakuritu=(double)(p-1)/p;
		double tmp=1;
		rep(j,cnt)tmp*=kakuritu;
		double tmp2=1;
		rep(j,n)tmp2*=tmp;
		ans=max(ans,1-tmp2);
	}
	cout<<fixed<<setprecision(15)<<ans<<endl;
	return 0;
}

//メイン
int main(){
	while(solve()==0);
	return 0;
}
