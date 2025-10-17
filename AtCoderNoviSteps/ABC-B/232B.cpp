#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for (long long i=0;i<n;i++)
#define loop(i,m,n) for(long long i=m;i<=n;i++)
#define ll long long
#define vl vector<long long>
#define vvl vector<vector<long long>>
#define inf 4000000000000000000LL
#define mod 998244353
int main(){
	string s,t;
	cin>>s>>t;
	rep(j,26){
		bool f=true;
		rep(i,s.size()){
			if(s[i]!=t[i])f=false;
			if(s[i]=='z')s[i]='a';
			else s[i]++;
		}
		if(f){
			cout<<"Yes"<<endl;
			return 0;
		}
	}
	cout<<"No"<<endl;
	return 0;
}