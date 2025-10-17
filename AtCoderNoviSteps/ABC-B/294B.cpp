#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	ll h,w;
	cin>>h>>w;
	rep(i,h){
		rep(j,w){
			ll a;
			cin>>a;
			if(a==0)cout<<'.';
			else cout<<(char)('A'+a-1);
		}
		cout<<endl;
	}
	return 0;
}