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

	vl c;

	rep(i,s.size()){
		if(s[i]!=t[i])c.push_back(i);
	}

	if(c.size()==0){
		cout<<"Yes"<<endl;
	} else if(c.size()==2){
		if(t[c[0]]==s[c[1]]&&t[c[1]]==s[c[0]]&&c[0]+1==c[1]){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}else{
		cout<<"No"<<endl;
	}

	return 0;
}