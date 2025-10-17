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
	ll n;
	cin>>n;
	set<string>s;
	rep(i,n){
		string ss;
		cin>>ss;
		string rss(ss.size(),'a');
		rep(j,ss.size()){
			rss[j]=ss[ss.size()-j-1];
		}
		if(!s.count(ss)&&!s.count(rss))s.insert(ss);
		
	}
	cout<<s.size()<<endl;
	return 0;
}