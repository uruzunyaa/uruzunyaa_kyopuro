//#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define rrep(i,n) for (ll i=n-1;i>=(ll)0;i--)
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
#define eps 0.000000001
random_device rnd;// 非決定的な乱数生成器
mt19937 mt(rnd());// メルセンヌ・ツイスタの32ビット版、引数は初期シード


//メイン
int main(){
	ll n;
	cin>>n;
	vl a(n);
	rep(i,n)cin>>a[i];
	ll xr=a[0];

	//自由度があるかどうか。
	bool f=false;
	
	//偶数の基底
	vl basis;
	loop(i,1,n-1){
		xr^=a[i];
		ll e=a[i]^a[0];
		rep(j,basis.size()){
			e=min(e,e^basis[j]);
		}
		if(e)basis.push_back(e);
		else f=true;
	}

	ll ans=0;
	rrep(i,60){
		//次のbitを1にしても消えるかどうかをチェックする。
		ll tmp=ans+(1LL<<i);
		rep(j,basis.size()){
			tmp=min(tmp,tmp^basis[j]);
		}
		if(tmp<(1LL<<i)){
			ans+=(1LL<<i);
		}
	}

	if(f||n%4!=2||n==2||ans!=xr){
		cout<<ans<<endl;
		return 0;
	}
	//他のXORを探しに行く。
	rep(i,60){
		if((ans&(1LL<<i))==0)continue;
		ans-=(1LL<<i);
		//次のbitを1から0にしても消えるかどうかチェックする。
		ll tmp=ans;
		rep(j,basis.size()){
			tmp=min(tmp,tmp^basis[j]);
		}
		if(tmp<(1LL<<i)){
			rrep(j,i){
				//次のbitを1にしても消えるかどうかをチェックする。
				tmp=ans+(1LL<<j);
				rep(j,basis.size()){
					tmp=min(tmp,tmp^basis[j]);
				}
				if(tmp<(1LL<<j)){
					ans+=(1LL<<j);
				}
			}
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}
