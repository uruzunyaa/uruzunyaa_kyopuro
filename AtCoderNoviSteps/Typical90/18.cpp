#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)

//メイン
int main(){
	double t,l,x,y;
	cin>>t>>l>>x>>y;

	//lを半径に直す
	l/=2;

	ll q;
	cin>>q;
	while(q--){
		double e;
		cin>>e;

		//yz平面上での e/t 周回った場所の観覧車の中心からの角度
		double theta = (0.75-(e/t))*2*M_PI;

		//E8君の座標を求める
		double height = l + sin(theta)*l;
		double E8_Y = cos(theta)*l;

		//xy平面上での高橋直大像との距離を求める
		double dist = sqrt(x*x + (y-E8_Y)*(y-E8_Y));

		//俯角を求め、出力
		double ans = atan2(height,dist)*180/M_PI;
		cout<<fixed<<setprecision(15)<<ans<<endl;
	}
	return 0;
}
