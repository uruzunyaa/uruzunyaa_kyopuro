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
	vl h(3),w(3);
	rep(i,3)cin>>h[i];
	rep(i,3)cin>>w[i];

	vvl b(3,vl(3));
	ll ans=0;
	loop(i,1,28){
		loop(j,1,28){
			loop(k,1,28){
				loop(l,1,28){
					b[0][0]=i;
					b[0][1]=j;
					b[0][2]=h[0]-i-j;
					b[1][0]=k;
					b[1][1]=l;
					b[1][2]=h[1]-k-l;
					b[2][0]=w[0]-i-k;
					b[2][1]=w[1]-j-l;
					b[2][2]=h[2]-b[2][0]-b[2][1];
					if(w[2]!=b[0][2]+b[1][2]+b[2][2])continue;
					bool f=true;
					rep(x,3)rep(y,3)if(b[x][y]<=0)f=false;
					if(f)ans++;
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
