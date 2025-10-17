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
	if(s.size()!=8){
		cout<<"No"<<endl;
		return 0;
	}
	if(s[0]<'A'||'Z'<s[0]||s[7]<'A'||'Z'<s[7]||s[1]<'1'||'9'<s[1]){
		cout<<"No"<<endl;
		return 0;
	}
	loop(i,2,6){
		if(s[i]<'0'||'9'<s[i]){
			cout<<"No"<<endl;
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	return 0;
}