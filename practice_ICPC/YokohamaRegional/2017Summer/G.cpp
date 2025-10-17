#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define vl vector<ll>
#define vvl vector<vl>
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define loop(i, a, b) for (ll i = a; i <= b; ++i)

ll h,w,s;

bool dfs(ll i,ll j,ll k,vvl & a){
	if(k<0)return false;

	while(1){
		//今のi,jに矛盾があるか調べる
		
		//横
		loop(sj,0,j){
			ll sum = 0;
			loop(z,sj,j){
				sum+=a[i][z];
			}
			if(sum>s){
				loop(z,sj,j){
					if(a[i][z]<=0)continue;
					a[i][z]*=-1;
					if(dfs(i,j,k-1,a))return true;
					a[i][z]*=-1;
				}
				return false;
			}
		}

		//縦
		rep(si,i){
			ll sum = 0;
			loop(z,si,i){
				sum+=a[z][j];
			}
			if(sum>s){
				loop(z,si,i){
					if(a[z][j]<=0)continue;
					a[z][j]*=-1;
					if(dfs(i,j,k-1,a))return true;
					a[z][j]*=-1;
				}
				return false;
			}
		}

		//問題ないので次へ
		j++;
		if(j==w){
			j=0;
			i++;
		}
		if(h==i){
			//デバッグ
			return true;
		}
	}
}

int main() {
	ll k;
	cin>>h>>w>>k>>s;
	vvl a;
	a = vvl(h,vl(w));
	rep(i,h)rep(j,w)cin>>a[i][j];

	if(dfs(0,0,k,a))cout<<"Yes"<<endl;
	else cout<<"No"<<endl;

    return 0;
}