#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
int main(){
	string s;
	cin>>s;
	ll b;
	ll r=0;
	rep(i,8){
		if(s[i]=='B')b+=i;
		if(s[i]=='K')r--;
		if(s[i]=='R')r++;
		if(r!=0&&s[i]=='K'){
			cout<<"No"<<endl;
			return 0;
		}
	}
	if(b%2==0)cout<<"No"<<endl;
	else cout<<"Yes"<<endl;
	
	return 0;
}