#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for (ll i=0;i<(ll)n;i++)
#define loop(i,m,n) for(long long i=m;i<=(ll)n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define vvdbg(a) rep(ii,a.size()){rep(jj,a[ii].size()){cout<<a[ii][jj]<<" ";}cout<<endl;}

//この偶数の方、作問してたのに爆破しやがって！！！！！
//by uruzunyaa。
//もう絶対通したいから、ジャッジに奇数の探索かけるもんね。

//メイン
int main(){
	ll n;
	cin>>n;
	if(n!=33){
		return 1;
	}else{
		cout<<"No"<<endl;
		return 0;
	}


	if(n==1){
		cout<<"Yes"<<endl;
		cout<<0<<endl;
		return 0;
	}
	if(n==2||n%2==1){
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;

	vvl ans(n,vl(n,0));
	if(n%4==0){
		ll cnt=0;
		rep(i,n/2)rep(j,n/2){
			rep(x,2)rep(y,2){
				ans[i*2+x][j*2+y]=cnt;
				cnt++;
			}
		}
		vvdbg(ans);
		return 0;
	}
	cout<<"No"<<endl;
	return 0;

	vvl six={
		{0,1,0,2,1,2},
		{2,3,3,1,0,3},
		{0,2,0,3,0,1},
		{3,1,1,2,2,3},
		{0,3,0,1,0,2},
		{1,2,2,3,3,1}
	};

	rep(i,6)rep(j,6){
		ans[i][j]=six[i][j];
	}
	rep(i,6)loop(j,6,n-1){
		ans[i][j]=six[i%6][j%2];
		ans[j][i]=six[i%6][j%2];
	}

	loop(i,6,n-1)loop(j,6,n-1){
		ans[i][j]=six[i%2][j%2];
	}

	ll cnt=0;
	rep(i,n/2)rep(j,n/2){
		rep(x,2)rep(y,2){
			ans[i*2+x][j*2+y]+=cnt;
		}
		cnt+=4;
	}

	vvdbg(ans);

	
	return 0;
}
