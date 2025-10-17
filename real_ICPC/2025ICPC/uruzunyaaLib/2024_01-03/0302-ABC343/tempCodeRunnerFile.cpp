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

//グリッド問題等用
vl dx={1,0,-1,0};
vl dy={0,1,0,-1};

//整数同士の累乗の計算をする。
ll power(ll A, ll B) {
	ll result = 1;
	for (ll i=0;i<B;i++){
		result *= A;
	}
	return result;
}

//メイン
int main(){
	vl v(3);
	rep(i,3)cin>>v[i];

	rep(a,15)rep(b,15)rep(c,15){
		rep(x,15)rep(y,15)rep(z,15){
			ll one=3*power(7,3);
			ll two=0;
			two+=max(0LL,min(7LL,a)+7-max(7LL,a))*max(0LL,min(7LL,b)+7-max(7LL,b))*max(0LL,min(7LL,c)+7-max(7LL,c));
			two+=max(0LL,min(7LL,x)+7-max(7LL,x))*max(0LL,min(7LL,y)+7-max(7LL,y))*max(0LL,min(7LL,z)+7-max(7LL,z));
			two+=max(0LL,min(a,x)+7-max(a,x))*max(0LL,min(b,y)+7-max(b,y))*max(0LL,min(c,z)+7-max(c,z));
			one-=two*2;
			ll three=0;
			three+=max(0LL,7-max(a,x))*max(0LL,7-max(b,y))*max(0LL,7-max(c,z));
			two-=three*3;
			one+=three*3;
			
			// cout<<one<<" "<<two<<" "<<three<<endl;
			// return 0;

			if(v[0]==one&&v[1]==two&&v[2]==three){
				cout<<"Yes"<<endl;
				cout<<"0 0 0 "<<a<<" "<<b<<" "<<c<<" "<<x<<" "<<y<<" "<<z<<endl;
				return 0;
			}
		}
	}
	cout<<"No"<<endl;
	return 0;
}
