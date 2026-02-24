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
#define vpdbg(a) rep(ii,a.size()){cout<<"{"<<a[ii].first<<","<<a[ii].second<<"} ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL
//#define mod 1000000007LL

//メイン
int main(){
	ll n,x;
	cin>>n>>x;
	vector<double> p(n);
	rep(i,n)cin>>p[i],p[i]/=100.0;

	//dpc[n][i] = 1パック開封した時、i個のレアカードがある確率
	vector<vector<double>> dpc(n+1,vector<double>(n+1,0));
	dpc[0][0]=1;
	rep(i,n){
		rep(j,n){
			dpc[i+1][j]+=dpc[i][j]*(1.0-p[i]);
			dpc[i+1][j+1]+=dpc[i][j]*p[i];
		}
	}

	//1枚以上のカードが出るまでに掛かる回数の期待値
	double k = 1.0/(1.0-dpc[n][0]);

	//遷移先の確率に置き換え(自己ループの確率を除外)
	loop(i,1,n){
		dpc[n][i]/=(1.0-dpc[n][0]);
	}

	//dp[i] = カードが丁度i個出る場合が発生する{確率,期待値}
	vector<pair<double,double>> dp(x+1,{0,0});
	dp[0]={1,0};
	rep(i,x){
		//遷移確率が0ならスキップ
		if(dp[i]==make_pair(0.0,0.0))continue;
		
		//この場所にたどり着く確率で補正
		dp[i].second/=dp[i].first;
		
		loop(j,1,n){
			dp[min(i+j,x)].first+=dp[i].first*dpc[n][j];
			dp[min(i+j,x)].second+=(dp[i].second+k)*dpc[n][j]*dp[i].first;
		}
	}
	cout<<fixed<<setprecision(15)<<dp[x].second<<endl;
	return 0;
}
