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
	vl x(8),y(8);
	rep(i,4){
		cin>>x[i]>>y[i];
		x[i+4]=x[i];
		y[i+4]=y[i];
	}
	rep(i,4){
		double theta=atan2(y[i+2]-y[i+1],x[i+2]-x[i+1])-atan2(y[i]-y[i+1],x[i]-x[i+1]);
		if(sin(theta)>0){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}
