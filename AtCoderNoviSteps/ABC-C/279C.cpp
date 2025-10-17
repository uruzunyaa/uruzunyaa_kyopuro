#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (long long i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define vdbg(a) rep(ii,a.size()){cout<<a[ii]<<" ";}cout<<endl;
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}
#define setdbg(a) for(const auto & ii:a){cout<<ii<<" ";}cout<<endl;
#define inf 4000000000000000000LL
#define mod 998244353LL

//メイン
int main(){
	ll h,w;
	cin>>h>>w;
	vector<string>s(h),t(h);
	rep(i,h)cin>>s[i];
	rep(i,h)cin>>t[i];

	vector<string> invs(w,string(h,'.')),invt(w,string(h,'.'));
	rep(i,h)rep(j,w){
		invs[j][i]=s[i][j];
		invt[j][i]=t[i][j];
	}
	sort(invs.begin(),invs.end());
	sort(invt.begin(),invt.end());
	if(invs==invt)cout<<"Yes"<<endl;
	else cout<<"No"<<endl;
	return 0;
}
