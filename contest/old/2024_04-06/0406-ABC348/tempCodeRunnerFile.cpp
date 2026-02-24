#pragma GCC optimize("O3");
#include<iostream>//入出力
using namespace std;
#define sh short int
#define rep(i,n) for (int i=0;i<n;i++)
//メイン
int main(){
	int n,m;
	cin>>n>>m;
	sh a[n][m];
	rep(i,n)rep(j,m)cin>>a[i][j];
	int ans=0;
	rep(i,n)rep(j,i){
		int cnt=0;
		rep(k,m)cnt+=a[i][k]==a[j][k];
		ans+=cnt%2;
	}
	cout<<ans<<endl;
	return 0;
}
