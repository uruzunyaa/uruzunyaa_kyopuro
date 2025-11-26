#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (ll i = 0; i < n; ++i)
#define rrep(i, n) for (ll i = n-1; i >=0; i--)
#define loop(i,m,n)for(ll i=m;i<=n;i++)
#define vl vector<ll>
#define vvl vector<vl>
#define inf 1000000000000000000LL

//拡大係数行列を与えると、連立1次方程式の解を返す。
template <typename T>
vector<T> hakidasi(vector<vector<T>> a){
	ll n=a.size();
	//下三角行列を0、対角行列を1にする
	rep(i,n){
		//i,iが0なら別の行とswap;
		if(a[i][i]==0){
			loop(j,i+1,n-1){
				if(a[j][i]!=0){
					swap(a[i],a[j]);
					break;
				}
			}
		}

		//i行目をa[i][i]で割る
		loop(j,i+1,n){
			a[i][j]/=a[i][i];
		}
		a[i][i]=1;

		//i行目より下の行を前の部分を0にする
		loop(j,i+1,n-1){
			//j行目のi番目を0にする
			loop(k,i+1,n){
				a[j][k]-=a[j][i]*a[i][k];
			}
			a[j][i]=0;
		}
	}
	vector<T> ans(n);
	//復元する。
	rrep(i,n){
		//i番目の答えを求める
		T tmp=a[i][n];
		loop(j,i+1,n-1){
			tmp-=a[i][j]*ans[j];
		}
		ans[i]=tmp;
	}
	return ans;
}

int main(){
	ll n;
	cin>>n;
	vector<vector<double>> mt(n,vector<double>(n+1));
	rep(i,n){
		rep(j,n+1){
			cin>>mt[i][j];
		}
	}
	vector<double> ans=hakidasi(mt);
	rep(i,n)cout<<ans[i]<<endl;
}